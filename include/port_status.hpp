#pragma once

#include <string>

struct PortStatus {
    int port{};
    bool open{false};

    std::string service;
    std::string banner;

    int response_time{-1};  // время проверки порта (мс)
};