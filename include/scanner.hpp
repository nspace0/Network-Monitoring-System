#pragma once

#include "device.hpp"

#include <vector>

class Scanner
{
public:
    void Scan(const std::vector<Device>& devices);
};