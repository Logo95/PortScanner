// ThreadPool.h
#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(int numThreads);
    ~ThreadPool();
    void enqueueTask(std::function<void()> task);
    void shutdown();
    void incrementActiveThreads();
    void decrementActiveThreads();
    int getActiveThreads() const;
    int getMaxThreads() const;
    std::mutex& getMtx();

private:
    void worker();
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> done;
    std::atomic<int> activeThreads;
    const int maxThreads;
};
