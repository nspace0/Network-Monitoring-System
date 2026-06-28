#include "../include/os_detector.hpp"

#include <array>
#include <cstdio>
#include <regex>

std::string OSDetector::Detect(const std::string& ip) {
#ifdef __linux__

    std::string cmd = "ping -c 1 -W 1 " + ip + " 2>/dev/null";

    FILE* pipe = popen(cmd.c_str(), "r");

    if (!pipe) return "Unknown";

    std::array<char, 256> buffer{};
    std::string output;

    while (fgets(buffer.data(), buffer.size(), pipe)) output += buffer.data();

    pclose(pipe);

    std::regex ttl_regex("ttl=([0-9]+)");
    std::smatch match;

    if (!std::regex_search(output, match, ttl_regex)) return "Unknown";

    int ttl = std::stoi(match[1]);

    if (ttl <= 64) return "Linux";

    if (ttl <= 128) return "Windows";

    if (ttl <= 255) return "Network Device";

#endif

    return "Unknown";
}