#pragma once

#include <vector>

#include "config.hpp"
#include "device.hpp"
#include "scan_result.hpp"

class Scanner {
   public:
    explicit Scanner(const Config& config);

    std::vector<ScanResult> Scan(const std::vector<Device>& devices,
                                 const std::vector<int>& ports);

   private:
    ScanResult ScanDevice(const Device& device, const std::vector<int>& ports);

    Config config_;
};