#pragma once

#include <string>

struct Config {
    int thread_count = 8;

    int ping_timeout = 1000;

    int connect_timeout = 1000;

    int banner_timeout = 2000;

    bool enable_ping = true;

    bool enable_banner = true;

    bool generate_html = true;

    bool generate_csv = true;

    bool generate_txt = true;

    static Config Load(const std::string& file);
};