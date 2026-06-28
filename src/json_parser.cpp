#include "../include/json_parser.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

std::vector<Device> JsonParser::Parse()
{
    CheckFile();

    namespace fs = std::filesystem;

    fs::path config_path = fs::current_path() / ".." / "config" / "devices.json";

    std::ifstream file(config_path);

    json j;

    file >> j;

    std::vector<Device> devices;

    for (const auto& item : j.at("devices"))
    {
        Device device;

        device.name     = item.at("name");
        device.type     = item.at("type");
        device.location = item.at("location");
        device.model    = item.at("model");
        device.ip       = item.at("ip");
        device.mac      = item.at("mac");
        device.vlan     = item.at("vlan");

        device.credentials.login = item.at("credentials").at("login");

        device.credentials.password = item.at("credentials").at("password");

        devices.push_back(device);
    }

    return devices;
}

void JsonParser::CheckFile()
{
    namespace fs = std::filesystem;

    fs::path file = fs::current_path() / ".." / "config" / "network.json";

    if (!fs::exists(file))
    {
        throw std::runtime_error("config/network.json not found.");
    }
}