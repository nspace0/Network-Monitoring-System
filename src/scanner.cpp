#include "../include/scanner.hpp"

#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>

#include "../include/banner_grabber.hpp"
#include "../include/os_detector.hpp"
#include "../include/ping.hpp"
#include "../include/port_scanner.hpp"
#include "../include/services.hpp"
#include "../include/thread_pool.hpp"

Scanner::Scanner(const Config& config) : config_(config) {}

std::vector<ScanResult> Scanner::Scan(const std::vector<Device>& devices,
                                      const std::vector<int>& ports) {
    std::vector<ScanResult> results;

    std::mutex mutex;

    ThreadPool pool(config_.thread_count);

    for (const auto& device : devices) {
        pool.Enqueue([&, device]() {
            ScanResult result = ScanDevice(device, ports);

            std::lock_guard lock(mutex);

            results.push_back(std::move(result));
        });
    }

    pool.Wait();

    return results;
}

ScanResult Scanner::ScanDevice(const Device& device,
                               const std::vector<int>& ports) {
    ScanResult result;

    result.device = device;

    Ping ping;

    result.ping = ping.Check(device.ip);

    if (result.ping) {
        result.latency = static_cast<int>(ping.Latency(device.ip));

        OSDetector detector;
        result.os = detector.Detect(device.ip);
    } else {
        result.latency = -1;
        result.os = "Unknown";
    }

    // Всегда продолжаем сканирование портов

    PortScanner scanner;

    std::mutex ports_mutex;

    ThreadPool pool(config_.thread_count);

    for (int port : ports) {
        pool.Enqueue([&, port]() {
            PortStatus status;

            status.port = port;

            auto start = std::chrono::steady_clock::now();

            status.open =
                scanner.IsOpen(device.ip, port, config_.connect_timeout);

            auto end = std::chrono::steady_clock::now();

            status.response_time =
                std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                      start)
                    .count();

            status.service = GetServiceName(port);

            if (status.open) {
                BannerGrabber grabber;
                status.banner =
                    grabber.Grab(device.ip, port, config_.banner_timeout);
            }

            std::lock_guard<std::mutex> lock(ports_mutex);
            result.ports.push_back(std::move(status));
        });
    }

    pool.Wait();

    std::sort(result.ports.begin(), result.ports.end(),
              [](const PortStatus& a, const PortStatus& b) {
                  return a.port < b.port;
              });

    return result;
}