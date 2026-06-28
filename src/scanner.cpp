#include "../include/port_scanner.hpp"

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

bool PortScanner::IsOpen(const std::string& ip,
                         int port,
                         int timeout_ms)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        return false;

    // Делаем сокет неблокирующим
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    int result = connect(sock,
                         (sockaddr*)&addr,
                         sizeof(addr));

    if (result == 0)
    {
        close(sock);
        return true;
    }

    fd_set fdset;

    FD_ZERO(&fdset);
    FD_SET(sock, &fdset);

    timeval tv;

    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    result = select(sock + 1,
                    nullptr,
                    &fdset,
                    nullptr,
                    &tv);

    if (result == 1)
    {
        int so_error;
        socklen_t len = sizeof(so_error);

        getsockopt(sock,
                   SOL_SOCKET,
                   SO_ERROR,
                   &so_error,
                   &len);

        close(sock);

        return so_error == 0;
    }

    close(sock);

    return false;
}