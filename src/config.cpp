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

    const auto& settings = j.at("settings");

    Config cfg;

    cfg.thread_count = settings.value("thread_count", 8);

    cfg.ping_timeout = settings.value("ping_timeout", 1000);

    cfg.connect_timeout = settings.value("connect_timeout", 1000);

    cfg.banner_timeout = settings.value("banner_timeout", 2000);

    cfg.enable_ping = settings.value("enable_ping", true);

    cfg.enable_banner = settings.value("enable_banner", true);

    cfg.generate_html = settings.value("generate_html", true);

    cfg.generate_csv = settings.value("generate_csv", true);

    cfg.generate_txt = settings.value("generate_txt", true);

    return cfg;
}