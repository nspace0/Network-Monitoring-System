#pragma once

#include <string>

#include "scan_result.hpp"

class DeviceDetector {
   public:
    std::string Detect(const ScanResult& result) const;
};