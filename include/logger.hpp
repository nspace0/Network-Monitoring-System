struct ScanResult
{
    bool ping = false;

    bool ssh = false;

    bool telnet = false;

    bool http = false;

    bool https = false;

    bool snmp = false;

    double latency = 0;

    std::string error;
};