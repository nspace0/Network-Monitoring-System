#pragma once

#include <string>
#include <vector>

class NetworkDiscovery {
   public:
    std::vector<std::string> Discover(const std::string& network);
};