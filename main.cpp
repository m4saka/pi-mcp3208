#include <iostream>
#include <iomanip> // std::fixed, std::setprecision
#include <cstdlib> // std::system
#include <wiringPi.h>
#include "mcp3208.hpp"

int main()
{
    if (wiringPiSetup() == -1)
    {
        std::cerr << "Unable to start wiringPi\n";
        return 1;
    }

    constexpr int SPI_CHANNEL = 0; // SPIのチャンネル番号(0または1)
    constexpr int PIN_CS = 8;      // CS(チップセレクト)のピン番号
    constexpr double V_REF = 3.3;  // V_refピンに入力している基準電圧(V単位)

    MCP3208 mcp3208(SPI_CHANNEL, PIN_CS, V_REF);

    // 出力を小数点以下4桁にする
    std::cout << std::fixed << std::setprecision(4);

    // 現在の電圧値を連続表示
    while (true)
    {
        mcp3208.update();

        // 各チャンネルの電圧値を画面に出力
        std::system("clear");
        for (int i = 0; i < 8; ++i)
        {
            std::cout
                << "CH" << i << ": " << mcp3208.voltageAt(i) << " [V]"
                << " (Raw:" << mcp3208.rawValueAt(i) << ")\n";
        }
        std::cout << std::flush;

        // 1秒待機
        delay(1000);
    }

    return 0;
}
