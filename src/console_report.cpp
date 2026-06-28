#include "../include/console_report.hpp"

#include "../include/colors.hpp"

#include <iostream>

void PrintResult(const ScanResult& result)
{
    std::cout << "========================================\n";

    std::cout << "Устройство : "
              << result.device.name
              << '\n';

    std::cout << "IP         : "
              << result.device.ip
              << '\n';

    std::cout << "PING       : ";
    std::cout << "Latency   : ";

if (result.latency >= 0)
{
    std::cout << Color::Green
              << result.latency
              << " ms";
}
else
{
    std::cout << Color::Red
              << "N/A";
}

std::cout << Color::Reset << '\n';

    if (result.ping)
    {
        std::cout << Color::Green
                  << "OK"
                  << Color::Reset
                  << '\n';
    }
    else
    {
        std::cout << Color::Red
                  << "FAIL"
                  << Color::Reset
                  << '\n';

        std::cout << "========================================\n\n";
        return;
    }

    std::cout << '\n';

    for (const auto& port : result.ports)
    {
        std::cout << "PORT "
                  << port.port
                  << " : ";

        if (port.open)
        {
            std::cout << Color::Green
                      << "OPEN";
        }
        else
        {
            std::cout << Color::Red
                      << "CLOSED";
        }

        std::cout << Color::Reset
                  << '\n';
    }

    std::cout << "========================================\n\n";
}