#include "mcp3208.hpp"
#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

namespace
{
    // SPIのクロック周波数(Hz単位)
    // (wiringPiのマニュアルだと推奨値500000以上らしいが問題なし?)
    constexpr int SPI_CLOCK_SPEED = 100000;

    // 基準電圧(V単位)
    constexpr double V_REF = 3.3;

    // 基準電圧と同じ場合の生の値
    constexpr double RAW_VALUE_REF = 4096.0;

    // SPI通信を初期化
    bool initSpi(int channel)
    {
        if (wiringPiSPISetup(channel, SPI_CLOCK_SPEED) == -1)
        {
            std::cerr << "Error: Failed to initialize SPI\n";
            return false;
        }
        return true;
    }
}

MCP3208::MCP3208(int spiChannel, int pinCs, double vRef)
    : m_spiChannel(spiChannel)
    , m_pinCs(pinCs)
    , m_vRef(vRef)
    , m_spiInitialized(initSpi(spiChannel))
{
    if (!m_spiInitialized)
    {
        // SPI通信の初期化に失敗した場合は何もせず0を返す
        m_rawValues.fill(0);
        return;
    }

    // CS(チップセレクト)のピンを出力モードにする
    pinMode(pinCs, OUTPUT);

    // 初回更新
    update();
}

void MCP3208::update()
{
    if (!m_spiInitialized) return;

    // 各チャンネルの値を更新
    for (unsigned char ch = 0; ch < CH_COUNT; ++ch)
    {
        digitalWrite(m_pinCs, LOW);

        // 生の値を取得
        unsigned char buffer[3];
        buffer[0] = (ch >> 2) | 0b00000110;
        buffer[1] = (ch << 6);
        buffer[2] = 0b00000000;
        wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);

        // 配列の値を更新
        m_rawValues[ch] = ((0b00001111 & buffer[1]) << 8) | buffer[2];

        digitalWrite(m_pinCs, HIGH);
    }
}

unsigned char MCP3208::rawValueAt(int ch) const
{
    return m_rawValues[ch];
}

double MCP3208::voltageAt(int ch) const
{
    // 値を基準電圧でスケーリングして返す
    return static_cast<double>(m_rawValues[ch]) * m_vRef / RAW_VALUE_REF;
}
