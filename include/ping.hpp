#pragma once

#include <string>

class Ping
{
public:
    // Возвращает true, если хост отвечает
    bool Check(const std::string& ip);

    // Возвращает задержку в миллисекундах
    double Latency(const std::string& ip);
};