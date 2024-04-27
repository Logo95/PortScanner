// WinsockManager.cpp
#include "WinsockManager.h"

WinsockManager::WinsockManager() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        throw std::runtime_error("WSAStartup failed with error: " + std::to_string(result));
    }
}

WinsockManager::~WinsockManager() {
    WSACleanup();
}
