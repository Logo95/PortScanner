// ThreadPool.h
#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

// Класс для управления пулом потоков и асинхронной обработкой задач.
class ThreadPool {
public:
    ThreadPool(int numThreads);
    ~ThreadPool();
    // Метод для добавления задачи в очередь.
    void enqueueTask(std::function<void()> task);
    // Метод для остановки всех потоков и очистки очереди задач.
    void shutdown();

    void incrementActiveThreads();
    void decrementActiveThreads();
    int getActiveThreads() const;
    int getMaxThreads() const;
    std::mutex& getMtx();

private:
    // Функция потока, обрабатывающая задачи из очереди.
    void worker();

    std::vector<std::thread> workers; // Вектор работающих потоков.
    std::queue<std::function<void()>> tasks; // Очередь задач.
    std::mutex mtx; // Мьютекс для синхронизации доступа к очереди.
    std::condition_variable cv; // Переменная для управления состоянием очереди.
    std::atomic<bool> done; // Флаг для остановки потоков.
    std::atomic<int> activeThreads; // Счётчик активных потоков.
    const int maxThreads; // Максимальное количество потоков.
};
