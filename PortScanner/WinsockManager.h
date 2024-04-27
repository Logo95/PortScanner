// WinsockManager.h
#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdexcept>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

// Класс для управления инициализацией и очисткой ресурсов Winsock.
class WinsockManager {
public:
    WinsockManager();
    ~WinsockManager();
};

