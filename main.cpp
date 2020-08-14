#include <iostream>
#include <iomanip> // std::fixed, std::setprecision
#include <vector>
#include <cstdlib> // std::system
#include <wiringPi.h>
#include "mcp3208.hpp"

namespace
{
    void displayValues(const MCP3208 & mcp3208)
    {
        for (int i = 0; i < 8; ++i)
        {
            std::cout
                << "CH" << i << ": " << mcp3208.voltageAt(i) << " [V]"
                << " (Raw:" << mcp3208.rawValueAt(i) << ")\n";
        }
    }
}

int main()
{
    if (wiringPiSetup() == -1)
    {
        std::cerr << "Unable to start wiringPi\n";
        return 1;
    }

    constexpr int SPI_CHANNEL_COUNT = 2; // SPI通信のチャンネルの個数
    constexpr int PIN_CS = 8;            // CS(チップセレクト)のピン番号
    constexpr double V_REF = 3.3;        // V_refピンに入力している基準電圧(V単位)

    // MCP3208のインスタンスをSPI通信のチャンネルごとに生成
    std::vector<MCP3208> mcp3208s;
    for (int channel = 0; channel < SPI_CHANNEL_COUNT; ++channel)
    {
        mcp3208s.emplace_back(i, PIN_CS, V_REF);
    }

    // 出力を小数点以下4桁にする
    std::cout << std::fixed << std::setprecision(4);

    // 現在の電圧値を連続表示
    while (true)
    {
        for (auto & mcp3208 : mcp3208s)
        {
            mcp3208.update();
        }

        // 電圧値を画面に出力
        std::system("clear");
        for (const auto & mcp3208 : mcp3208s)
        {
            std::cout << "<< SPI Channel " << mcp3208.spiChannel() << " >>\n";
            displayValues(mcp3208);
            std::cout << std::endl;
        }

        // 1秒待機
        delay(1000);
    }

    return 0;
}
