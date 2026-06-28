#pragma once

#include <vector>

#include "device.hpp"
#include "port_status.hpp"

struct ScanResult {
    Device device;

    bool ping = false;

    int latency = 0;

    std::vector<PortStatus> ports;
    std::string os;
};