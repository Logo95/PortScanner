#include "ValidCheck.h"
#include <ws2tcpip.h> // Для функции inet_pton
#include <cstdlib> // Для std::atoi

ValidCheck::ValidCheck(int argc, char* argv[]) : validConfig(false), startPort(0), endPort(0) {
    if (argc != 4) return;

    ipAddress = argv[1];
    if (!validateIpAddress(ipAddress)) return;

    std::string startPortStr = argv[2];
    std::string endPortStr = argv[3];
    if (!validatePort(startPortStr) || !validatePort(endPortStr)) return;

    startPort = std::stoi(startPortStr);
    endPort = std::stoi(endPortStr);

    if (startPort > endPort) return;

    validConfig = true;
}

bool ValidCheck::isValid() const {
    return validConfig;
}

std::string ValidCheck::getIpAddress() const {
    return ipAddress;
}

int ValidCheck::getStartPort() const {
    return startPort;
}

int ValidCheck::getEndPort() const {
    return endPort;
}

bool ValidCheck::validateIpAddress(const std::string& ip) const {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 0;
}

bool ValidCheck::validatePort(const std::string& portStr) const {
    try {
        int port = std::stoi(portStr);
        return port > 0 && port <= 65535;
    }
    catch (...) {
        return false;
    }
}
