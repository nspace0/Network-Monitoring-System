#include <iostream>

#include "../include/json_parser.hpp"
#include "../include/port_scanner.hpp"

int main()
{
    try
    {
        JsonParser parser;

        auto devices = parser.Parse();

        PortScanner scanner;

        std::cout << "Loaded "
                  << devices.size()
                  << " devices\n\n";

        for (const auto& device : devices)
        {
            std::cout << "====================================\n";
            std::cout << device.name << '\n';
            std::cout << device.ip << '\n';

            std::cout << "SSH    : "
                      << (scanner.IsOpen(device.ip,22) ? "OPEN":"CLOSED")
                      << '\n';

            std::cout << "Telnet : "
                      << (scanner.IsOpen(device.ip,23) ? "OPEN":"CLOSED")
                      << '\n';

            std::cout << "HTTP   : "
                      << (scanner.IsOpen(device.ip,80) ? "OPEN":"CLOSED")
                      << '\n';

            std::cout << "HTTPS  : "
                      << (scanner.IsOpen(device.ip,443) ? "OPEN":"CLOSED")
                      << '\n';

            std::cout << "SNMP   : "
                      << (scanner.IsOpen(device.ip,161) ? "OPEN":"CLOSED")
                      << "\n\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}