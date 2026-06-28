#pragma once

#include <vector>

#include "device.hpp"
#include "scan_result.hpp"

class Scanner
{
public:
    std::vector<ScanResult> Scan(
        const std::vector<Device>& devices,
        const std::vector<int>& ports);

private:
    ScanResult ScanDevice(
        const Device& device,
        const std::vector<int>& ports);
};