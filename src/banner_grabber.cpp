#include "../include/banner_grabber.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include <cstring>
#include <string>

std::string BannerGrabber::Grab(const std::string& ip,
                                int port,
                                int timeout)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        return "";

    timeval tv{};
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) != 1)
    {
        close(sock);
        return "";
    }

    if (connect(sock,
                reinterpret_cast<sockaddr*>(&addr),
                sizeof(addr)) != 0)
    {
        close(sock);
        return "";
    }

    char buffer[1024]{};

    int bytes = recv(sock,
                     buffer,
                     sizeof(buffer) - 1,
                     0);

    close(sock);

    if (bytes <= 0)
        return "";

    buffer[bytes] = '\0';

    return std::string(buffer);
}