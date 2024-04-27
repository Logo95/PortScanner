// PortScanner.h
#pragma once
#include <string>
#include <vector>
#include "ThreadPool.h"

// Функция для проверки открытости порта на указанном IP-адресе.
void CheckPort(const std::string& ipAddress, int port, std::vector<int>& openPorts, ThreadPool& pool);
