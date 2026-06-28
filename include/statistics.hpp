#pragma once

#include <vector>

#include "scan_result.hpp"

class Statistics
{
public:
    static void Print(const std::vector<ScanResult>& results);
};