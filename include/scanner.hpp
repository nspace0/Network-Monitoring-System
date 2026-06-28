class Scanner
{
public:

    ScanResult Scan(const Device& device);

};

ScanResult Scanner::Scan(const Device& device)
{
    ScanResult result;

    result.ping = ping.Check(device.ip);

    result.ssh = portScanner.IsOpen(device.ip,22,2000);

    result.telnet = portScanner.IsOpen(device.ip,23,2000);

    result.http = portScanner.IsOpen(device.ip,80,2000);

    result.https = portScanner.IsOpen(device.ip,443,2000);

    result.snmp = portScanner.IsOpen(device.ip,161,2000);

    return result;
}