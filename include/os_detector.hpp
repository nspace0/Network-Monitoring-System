#pragma once

#include <string>

class OSDetector {
   public:
    std::string Detect(const std::string& ip);
};