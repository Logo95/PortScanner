// WinsockManager.cpp
#include "WinsockManager.h"

WinsockManager::WinsockManager() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        exit(1);
    }
}

WinsockManager::~WinsockManager() {
    WSACleanup();
}
