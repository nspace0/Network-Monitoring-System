#include "../include/config.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

Config Config::Load(const std::string& file) {
    std::ifstream input(file);

    if (!input) {
        throw std::runtime_error("Cannot open " + file);
    }

    json j;
    input >> j;

    Config cfg;

    cfg.thread_count = j.value("thread_count", 8);
    cfg.ping_timeout = j.value("ping_timeout", 1000);
    cfg.connect_timeout = j.value("connect_timeout", 1000);
    cfg.banner_timeout = j.value("banner_timeout", 2000);

    cfg.enable_ping = j.value("enable_ping", true);
    cfg.enable_banner = j.value("enable_banner", true);

    cfg.generate_html = j.value("generate_html", true);
    cfg.generate_csv = j.value("generate_csv", true);
    cfg.generate_txt = j.value("generate_txt", true);

    return cfg;
}