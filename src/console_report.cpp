#include "../include/console_report.hpp"

#include <iomanip>
#include <iostream>

#include "../include/colors.hpp"
#include "../include/services.hpp"

void PrintResult(const ScanResult& result) {
    std::cout << "========================================\n";

    std::cout << "Устройство : " << result.device.name << '\n';
    std::cout << "IP         : " << result.device.ip << '\n';

    std::cout << "PING       : ";

    if (result.ping) {
        std::cout << Color::Green << "OK" << Color::Reset;
    } else {
        std::cout << Color::Red << "FAIL" << Color::Reset;
    }

    std::cout << '\n';

    std::cout << "Latency    : ";

    if (result.latency >= 0) {
        std::cout << Color::Green << result.latency << " ms" << Color::Reset;
    } else {
        std::cout << Color::Yellow << "N/A" << Color::Reset;
    }

    std::cout << '\n';
    std::cout << '\n';

    for (const auto& port : result.ports) {
        std::cout << std::left << std::setw(8) << port.port << std::setw(15)
                  << port.service;

        if (port.open) {
            std::cout << Color::Green << "OPEN";
        } else {
            std::cout << Color::Red << "CLOSED";
        }

        std::cout << Color::Reset << '\n';

        if (!port.banner.empty()) {
            std::cout << "         " << Color::Blue << port.banner
                      << Color::Reset << '\n';
        }
    }

    std::cout << "========================================\n\n";
}