#include "../include/scanner.hpp"

#include "../include/ping.hpp"
#include "../include/port_scanner.hpp"
#include "../include/thread_pool.hpp"

#include <mutex>
#include <thread>

std::vector<ScanResult> Scanner::Scan(
    const std::vector<Device>& devices,
    const std::vector<int>& ports)
{
    std::vector<ScanResult> results;

    std::mutex mutex;

    ThreadPool pool(std::thread::hardware_concurrency());

    for (const auto& device : devices)
    {
        pool.Enqueue([&, device]()
        {
            ScanResult result =
                ScanDevice(device, ports);

            std::lock_guard lock(mutex);

            results.push_back(std::move(result));
        });
    }

    pool.Wait();

    return results;
}

ScanResult Scanner::ScanDevice(
    const Device& device,
    const std::vector<int>& ports)
{
    ScanResult result;

    result.device = device;

    Ping ping;

    result.ping = ping.Check(device.ip);

if (result.ping)
{
    result.latency = static_cast<int>(ping.Latency(device.ip));
}
else
{
    result.latency = -1;
    return result;
}

    PortScanner scanner;

    for (int port : ports)
    {
        PortStatus status;

        status.port = port;

        status.open =
            scanner.IsOpen(device.ip,
                           port);

        result.ports.push_back(status);
    }

    return result;
}