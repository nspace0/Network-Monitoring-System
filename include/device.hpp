#pragma once

#include <string>

struct Credentials
{
    std::string login;
    std::string password;
};

struct Device
{
    std::string name;

    std::string type;

    std::string location;

    std::string model;

    std::string ip;

    std::string mac;

    int vlan;

    Credentials credentials;
};