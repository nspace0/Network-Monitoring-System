#include "../include/services.hpp"

#include <unordered_map>

std::string GetServiceName(int port) {
    static const std::unordered_map<int, std::string> services = {
        {20, "FTP-DATA"},     {21, "FTP"},      {22, "SSH"},
        {23, "TELNET"},       {25, "SMTP"},     {53, "DNS"},
        {67, "DHCP"},         {68, "DHCP"},     {69, "TFTP"},
        {80, "HTTP"},         {110, "POP3"},    {123, "NTP"},
        {135, "RPC"},         {137, "NetBIOS"}, {138, "NetBIOS"},
        {139, "NetBIOS"},     {143, "IMAP"},    {161, "SNMP"},
        {389, "LDAP"},        {443, "HTTPS"},   {445, "SMB"},
        {502, "Modbus"},      {3306, "MySQL"},  {3389, "RDP"},
        {5432, "PostgreSQL"}, {5900, "VNC"},    {6379, "Redis"},
        {8080, "HTTP-ALT"}};

    auto it = services.find(port);

    if (it == services.end()) return "Unknown";

    return it->second;
}