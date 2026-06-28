#include "../include/network_discovery.hpp"

#include <mutex>
#include <sstream>

#include "../include/ping.hpp"
#include "../include/thread_pool.hpp"

std::vector<std::string> NetworkDiscovery::Discover(
    const std::string& network) {
    std::vector<std::string> alive;

    std::mutex mutex;

    ThreadPool pool(64);

    auto pos = network.find('/');

    std::string base = network.substr(0, pos);

    auto last = base.rfind('.');

    base = base.substr(0, last + 1);

    for (int i = 1; i < 255; ++i) {
        pool.Enqueue([&, i]() {
            Ping ping;

            std::string ip = base + std::to_string(i);

            if (ping.Check(ip)) {
                std::lock_guard lock(mutex);
                alive.push_back(ip);
            }
        });
    }

    pool.Wait();

    return alive;
}