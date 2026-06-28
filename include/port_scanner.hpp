#pragma once

#include <string>

class PortScanner
{
public:
    bool IsOpen(const std::string& ip,
                int port,
                int timeout_ms = 2000);
};