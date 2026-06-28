#pragma once

#include <string>

class BannerGrabber
{
public:
    std::string Grab(const std::string& ip,
                     int port,
                     int timeout = 2000);
};