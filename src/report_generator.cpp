#include "../include/report_generator.hpp"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

std::string ReportGenerator::GetTimeStamp() {
    auto now = std::time(nullptr);

    std::tm tm = *std::localtime(&now);

    std::ostringstream ss;

    ss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");

    return ss.str();
}

void ReportGenerator::SaveTxt(const std::vector<ScanResult>& results) {
    fs::create_directories("reports");

    std::ofstream file("reports/report_" + GetTimeStamp() + ".txt");

    for (const auto& device : results) {
        file << "========================================\n";

        file << device.device.name << '\n';
        file << device.device.ip << '\n';

        file << "Ping: " << (device.ping ? "OK" : "FAIL") << '\n';

        file << "Latency: ";

        if (device.latency >= 0)
            file << device.latency << " ms\n";
        else
            file << "N/A\n";

        for (const auto& port : device.ports) {
            file << port.port << " " << port.service << " "
                 << (port.open ? "OPEN" : "CLOSED");

            if (!port.banner.empty()) file << " | " << port.banner;

            file << '\n';
        }

        file << '\n';
    }
}

void ReportGenerator::SaveCsv(const std::vector<ScanResult>& results) {
    fs::create_directories("reports");

    std::ofstream file("reports/report_" + GetTimeStamp() + ".csv");

    file << "Device,IP,Ping,Latency,Port,Service,State,Banner\n";

    for (const auto& device : results) {
        for (const auto& port : device.ports) {
            file << device.device.name << ',' << device.device.ip << ','
                 << (device.ping ? "OK" : "FAIL") << ',';

            if (device.latency >= 0)
                file << device.latency;
            else
                file << "N/A";

            file << ',' << port.port << ',' << port.service << ','
                 << (port.open ? "OPEN" : "CLOSED") << ',' << port.banner
                 << '\n';
        }
    }
}

void ReportGenerator::SaveHtml(const std::vector<ScanResult>& results) {
    fs::create_directories("reports");

    std::ofstream file("reports/report_" + GetTimeStamp() + ".html");

    file << R"(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">

<style>

body
{
    font-family: Arial;
    background:#f5f5f5;
}

table
{
    border-collapse:collapse;
    width:100%;
}

th,td
{
    border:1px solid gray;
    padding:6px;
}

.open
{
    color:green;
    font-weight:bold;
}

.closed
{
    color:red;
    font-weight:bold;
}

</style>

</head>

<body>

<h2>Network Monitoring Report</h2>

<table>

<tr>

<th>Device</th>
<th>IP</th>
<th>Ping</th>
<th>Latency</th>
<th>Port</th>
<th>Service</th>
<th>Status</th>
<th>Banner</th>

</tr>
)";

    for (const auto& device : results) {
        for (const auto& port : device.ports) {
            file << "<tr>";

            file << "<td>" << device.device.name << "</td>";
            file << "<td>" << device.device.ip << "</td>";

            file << "<td>" << (device.ping ? "OK" : "FAIL") << "</td>";

            if (device.latency >= 0)
                file << "<td>" << device.latency << " ms</td>";
            else
                file << "<td>N/A</td>";

            file << "<td>" << port.port << "</td>";

            file << "<td>" << port.service << "</td>";

            if (port.open)
                file << "<td class='open'>OPEN</td>";
            else
                file << "<td class='closed'>CLOSED</td>";

            file << "<td>" << port.banner << "</td>";

            file << "</tr>";
        }
    }

    file << R"(

</table>

</body>

</html>

)";
}