#include "../include/statistics.hpp"

#include <iomanip>
#include <iostream>
#include <map>

#include "../include/colors.hpp"

void Statistics::Print(const std::vector<ScanResult>& results)
{
    int online = 0;
    int offline = 0;

    std::map<std::string, int> services;

    for (const auto& result : results)
    {
        if (result.ping)
            ++online;
        else
            ++offline;

        for (const auto& port : result.ports)
        {
            if (port.open)
                services[port.service]++;
        }
    }

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "Статистика\n";
    std::cout << "========================================\n";

    std::cout << std::left << std::setw(28)
              << "Всего устройств:"
              << results.size() << '\n';

    std::cout << std::left << std::setw(28)
              << "Ping OK:"
              << Color::Green << online
              << Color::Reset << '\n';

    std::cout << std::left << std::setw(28)
              << "Ping FAIL:"
              << Color::Red << offline
              << Color::Reset << "\n\n";

    std::cout << "Открытые сервисы:\n";

    if (services.empty())
    {
        std::cout << "  нет\n";
    }
    else
    {
        for (const auto& [service, count] : services)
        {
            std::cout << "  "
                      << std::setw(15)
                      << service
                      << count
                      << '\n';
        }
    }

    std::cout << "========================================\n";
}