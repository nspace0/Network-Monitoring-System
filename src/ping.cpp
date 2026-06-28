#include "../include/ping.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <regex>
#include <string>

bool Ping::Check(const std::string& ip)
{
#ifdef __linux__
    std::string cmd =
        "ping -c 1 -W 1 " + ip + " > /dev/null 2>&1";

    return system(cmd.c_str()) == 0;
#else
    return false;
#endif
}

double Ping::Latency(const std::string& ip)
{
#ifdef __linux__

    std::string cmd =
        "ping -c 1 -W 1 " + ip;

    std::array<char,128> buffer{};

    std::string result;

    FILE* pipe = popen(cmd.c_str(),"r");

    if(!pipe)
        return -1;

    while(fgets(buffer.data(),buffer.size(),pipe))
        result += buffer.data();

    pclose(pipe);

    std::regex r("time=([0-9\\.]+)");

    std::smatch match;

    if(std::regex_search(result,match,r))
        return std::stod(match[1]);

#endif

    return -1;
}