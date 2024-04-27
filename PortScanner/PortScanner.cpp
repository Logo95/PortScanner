#include "PortScanner.h"
#include "ThreadPool.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

void CheckPort(const std::string& ipAddress, int port, std::vector<int>& openPorts, ThreadPool& pool) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress.c_str(), &addr.sin_addr);
    addr.sin_port = htons(port);

    u_long mode = 1; // non-blocking mode
    ioctlsocket(sock, FIONBIO, &mode);

    connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    fd_set set;
    FD_ZERO(&set);
    FD_SET(sock, &set);
    timeval timeOut;
    timeOut.tv_sec = 0;
    timeOut.tv_usec = 10000; // 10 ms timeout

    if (select(0, NULL, &set, NULL, &timeOut) > 0) {
        int so_error;
        socklen_t len = sizeof(so_error);
        getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&so_error, &len);
        if (so_error == 0) {
            std::lock_guard<std::mutex> guard(pool.getMtx());
            openPorts.push_back(port);
            std::cout << "Port " << port << " is open." << std::endl;
        }
    }

    closesocket(sock);
    pool.decrementActiveThreads();
}
