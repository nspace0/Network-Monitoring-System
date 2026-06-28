#pragma once

#include <vector>

#include "device.hpp"

class JsonParser
{
public:
    std::vector<Device> Parse();

private:
    void CheckFile();
};