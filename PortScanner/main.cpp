#include "WinsockManager.h"
#include "ThreadPool.h"
#include "PortScanner.h"
#include "ValidCheck.h"
#include <iostream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]) {
    // Создание объекта конфигурации и проверка валидности аргументов.
    ValidCheck config(argc, argv);
    if (!config.isValid()) {
        std::cerr << "Usage: " << argv[0] << " <valid IP> <start port> <end port>\n";
        std::cerr << "Ensure the IP address and ports are valid and start port is less than or equal to end port." << std::endl;
        return 1;
    }

    std::vector<int> openPorts;

    // Инициализация менеджера Winsock.
    WinsockManager wsManager;
    // Создание пула потоков для многопоточной обработки.
    ThreadPool pool(50);

    // Замер времени начала сканирования.
    auto start = std::chrono::high_resolution_clock::now();

    // Раздача задач на сканирование портов.
    for (int port = config.getStartPort(); port <= config.getEndPort(); ++port) {
        // Ожидание доступности потока в пуле.
        while (pool.getActiveThreads() >= pool.getMaxThreads()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        pool.incrementActiveThreads();
        // Добавление задачи в пул потоков.
        pool.enqueueTask([ip = config.getIpAddress(), port, &openPorts, &pool]{
            CheckPort(ip, port, openPorts, pool);
            });
    }

    // Ожидание завершения всех потоков.
    pool.shutdown();

    // Замер времени окончания сканирования.
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    // Вывод результатов сканирования.
    std::cout << "Scanning complete.\nScanning took " << elapsed.count() << " seconds." << std::endl;

    return 0;
}
