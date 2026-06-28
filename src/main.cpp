#include <chrono>
#include <iostream>

#include "../include/json_parser.hpp"
#include "../include/port_scanner.hpp"

int main()
{
    auto start = std::chrono::steady_clock::now();

    try
    {
        JsonParser parser;
        auto       devices = parser.Parse();

        PortScanner scanner;

        std::cout << "Loaded " << devices.size() << " devices\n\n";

        for (const auto& device : devices)
        {
            std::cout << "====================================\n";
            std::cout << device.name << '\n';
            std::cout << device.ip << '\n';

            std::cout << "SSH    : " << (scanner.IsOpen(device.ip, 22) ? "OPEN" : "CLOSED") << '\n';

            std::cout << "Telnet : " << (scanner.IsOpen(device.ip, 23) ? "OPEN" : "CLOSED") << '\n';

            std::cout << "HTTP   : " << (scanner.IsOpen(device.ip, 80) ? "OPEN" : "CLOSED") << '\n';

            std::cout << "HTTPS  : " << (scanner.IsOpen(device.ip, 443) ? "OPEN" : "CLOSED")
                      << '\n';

            std::cout << "SNMP   : " << (scanner.IsOpen(device.ip, 161) ? "OPEN" : "CLOSED")
                      << "\n\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        long long total_seconds = duration.count();

        int hours   = total_seconds / 3600;
        int minutes = (total_seconds % 3600) / 60;
        int seconds = total_seconds % 60;

        std::cout << "\n========================================\n";
        std::cout << "Время выполнения программы\n";
        std::cout << hours << " ч " << minutes << " мин " << seconds << " сек\n";
        std::cout << "========================================\n";

        return EXIT_FAILURE;
    }

    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    long long total_seconds = duration.count();

    int hours   = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    std::cout << "\n========================================\n";
    std::cout << "Время выполнения программы\n";
    std::cout << hours << " ч " << minutes << " мин " << seconds << " сек\n";
    std::cout << "========================================\n";

    return EXIT_SUCCESS;
}