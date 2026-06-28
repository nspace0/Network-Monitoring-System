#include "../include/banner_grabber.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include <cstring>
#include <sstream>

std::string BannerGrabber::Grab(const std::string& ip, int port, int timeout) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) return "";

    timeval tv{};
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) != 1) {
        close(sock);
        return "";
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        close(sock);
        return "";
    }

    //----------------------------------------
    // HTTP
    //----------------------------------------

    if (port == 80 || port == 8080) {
        std::ostringstream request;

        request << "HEAD / HTTP/1.1\r\n"
                << "Host: " << ip << "\r\n"
                << "Connection: close\r\n\r\n";

        auto text = request.str();

        send(sock, text.c_str(), text.size(), 0);
    }

    //----------------------------------------
    // SMTP
    //----------------------------------------

    if (port == 25) {
        const char* cmd = "EHLO scanner\r\n";

        send(sock, cmd, strlen(cmd), 0);
    }

    //----------------------------------------
    // FTP
    //----------------------------------------

    if (port == 21) {
        const char* cmd = "QUIT\r\n";

        send(sock, cmd, strlen(cmd), 0);
    }

    //----------------------------------------

    char buffer[4096]{};

    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

    close(sock);

    if (bytes <= 0) return "";

    buffer[bytes] = '\0';

    std::string banner(buffer);

    //----------------------------------------
    // первая строка
    //----------------------------------------

    auto pos = banner.find('\n');

    if (pos != std::string::npos) banner.erase(pos);

    return banner;
}