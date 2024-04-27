// PortScanner.h
#pragma once
#include <string>
#include <vector>
#include "ThreadPool.h"  // �� �������� �������� ������������ ���� ThreadPool

void CheckPort(const std::string& ipAddress, int port, std::vector<int>& openPorts, ThreadPool& pool);
