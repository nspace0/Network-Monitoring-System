#include "../include/json_parser.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

namespace fs = std::filesystem;

static fs::path GetConfigPath() {
    fs::path current = fs::current_path();

    if (fs::exists(current / "config" / "devices.json"))
        return current / "config" / "devices.json";

    if (fs::exists(current.parent_path() / "config" / "devices.json"))
        return current.parent_path() / "config" / "devices.json";

    throw std::runtime_error("config/devices.json not found.");
}

void JsonParser::CheckFile() {
    if (!fs::exists(GetConfigPath())) {
        throw std::runtime_error("config/devices.json not found.");
    }
}

std::vector<Device> JsonParser::ParseDevices() {
    CheckFile();

    std::ifstream file(GetConfigPath());

    json j;

    file >> j;

    std::vector<Device> devices;

    for (const auto& item : j.at("devices")) {
        Device device;

        device.name = item.at("name");
        device.type = item.at("type");
        device.location = item.at("location");
        device.model = item.at("model");
        device.ip = item.at("ip");
        device.mac = item.at("mac");
        device.vlan = item.at("vlan");

        device.credentials.login = item.at("credentials").at("login");

        device.credentials.password = item.at("credentials").at("password");

        devices.push_back(device);
    }

    return devices;
}

std::vector<int> JsonParser::ParsePorts() {
    CheckFile();

    std::ifstream file(GetConfigPath());

    json j;

    file >> j;

    return j.at("ports").get<std::vector<int>>();
}