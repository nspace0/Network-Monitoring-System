#include "../include/device_detector.hpp"

std::string DeviceDetector::Detect(const ScanResult& result) const
{
    bool ssh = false;
    bool http = false;
    bool snmp = false;
    bool rdp = false;

    for (const auto& port : result.ports)
    {
        if (!port.open)
            continue;

        switch (port.port)
        {
            case 22:
                ssh = true;
                break;

            case 80:
            case 443:
            case 8080:
                http = true;
                break;

            case 161:
                snmp = true;
                break;

            case 3389:
                rdp = true;
                break;
        }
    }

    if (snmp && ssh)
        return "Switch / Router";

    if (rdp)
        return "Windows Server";

    if (http && !ssh)
        return "Web Device";

    if (ssh)
        return "Linux Device";

    return "Unknown";
}