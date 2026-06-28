#pragma once

#include <vector>

#include "device.hpp"

class JsonParser {
   public:
    std::vector<Device> ParseDevices();

    std::vector<int> ParsePorts();

   private:
    void CheckFile();
};