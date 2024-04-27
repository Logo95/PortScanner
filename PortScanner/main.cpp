#include "WinsockManager.h"
#include "ThreadPool.h"
#include "PortScanner.h"
#include <iostream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <IP> <start port> <end port>" << std::endl;
        return 1;
    }

    std::string ip = argv[1];
    int startPort = std::stoi(argv[2]);
    int endPort = std::stoi(argv[3]);
    std::vector<int> openPorts;

    WinsockManager wsManager;
    ThreadPool pool(50);

    auto start = std::chrono::high_resolution_clock::now();

    for (int port = startPort; port <= endPort; ++port) {
        while (pool.getActiveThreads() >= pool.getMaxThreads()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        pool.incrementActiveThreads();
        pool.enqueueTask([ip, port, &openPorts, &pool] { CheckPort(ip, port, openPorts, pool); });
    }

    pool.shutdown();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Scanning complete.\nScanning took " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
