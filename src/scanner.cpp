#include "../include/scanner.hpp"

#include "../include/colors.hpp"
#include "../include/port_scanner.hpp"
#include "../include/thread_pool.hpp"

#include <iostream>
#include <mutex>

void Scanner::Scan(const std::vector<Device>& devices)
{
    unsigned threads = std::thread::hardware_concurrency();

    if (threads == 0)
        threads = 4;

    threads *= 2;

    ThreadPool pool(threads);

    PortScanner scanner;

    std::mutex console;

    for (const auto& device : devices)
    {
        pool.Enqueue([&, device]()
        {
            bool ssh = scanner.IsOpen(device.ip, 22);
            bool telnet = scanner.IsOpen(device.ip, 23);
            bool http = scanner.IsOpen(device.ip, 80);
            bool https = scanner.IsOpen(device.ip, 443);
            bool snmp = scanner.IsOpen(device.ip, 161);

            std::lock_guard lock(console);

            std::cout
                << Color::Yellow
                << "========================================\n"
                << Color::Reset;

            std::cout
                << Color::Bold
                << device.name
                << Color::Reset
                << '\n';

            std::cout << "IP : " << device.ip << '\n';

            auto Print = [](const char* name, bool ok)
            {
                std::cout << name << " : ";

                if (ok)
                    std::cout << Color::Green << "OK";
                else
                    std::cout << Color::Red << "CLOSED";

                std::cout << Color::Reset << '\n';
            };

            Print("SSH   ", ssh);
            Print("Telnet", telnet);
            Print("HTTP  ", http);
            Print("HTTPS ", https);
            Print("SNMP  ", snmp);

            std::cout << '\n';
        });
    }

    pool.Wait();
}