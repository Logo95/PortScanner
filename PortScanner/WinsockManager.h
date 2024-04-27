// WinsockManager.h
#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

class WinsockManager {
public:
    WinsockManager();
    ~WinsockManager();
};

