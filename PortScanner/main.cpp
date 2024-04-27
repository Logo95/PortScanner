#include "WinsockManager.h"
#include "ThreadPool.h"
#include "PortScanner.h"
#include "ValidCheck.h"
#include <iostream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]) {
    // �������� ������� ������������ � �������� ���������� ����������.
    ValidCheck config(argc, argv);
    if (!config.isValid()) {
        std::cerr << "Usage: " << argv[0] << " <valid IP> <start port> <end port>\n";
        std::cerr << "Ensure the IP address and ports are valid and start port is less than or equal to end port." << std::endl;
        return 1;
    }

    std::vector<int> openPorts;

    // ������������� ��������� Winsock.
    WinsockManager wsManager;
    // �������� ���� ������� ��� ������������� ���������.
    ThreadPool pool(50);

    // ����� ������� ������ ������������.
    auto start = std::chrono::high_resolution_clock::now();

    // ������� ����� �� ������������ ������.
    for (int port = config.getStartPort(); port <= config.getEndPort(); ++port) {
        // �������� ����������� ������ � ����.
        while (pool.getActiveThreads() >= pool.getMaxThreads()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        pool.incrementActiveThreads();
        // ���������� ������ � ��� �������.
        pool.enqueueTask([ip = config.getIpAddress(), port, &openPorts, &pool]{
            CheckPort(ip, port, openPorts, pool);
            });
    }

    // �������� ���������� ���� �������.
    pool.shutdown();

    // ����� ������� ��������� ������������.
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    // ����� ����������� ������������.
    std::cout << "Scanning complete.\nScanning took " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
