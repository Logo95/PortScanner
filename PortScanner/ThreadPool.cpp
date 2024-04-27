// ThreadPool.cpp
#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) : done(false), activeThreads(0), maxThreads(numThreads) {
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::enqueueTask(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.emplace(std::move(task));
    }
    cv.notify_one();
}

void ThreadPool::shutdown() {
    done = true;
    cv.notify_all();
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::worker() {
    while (!done || !tasks.empty()) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !tasks.empty() || done; });
            if (tasks.empty()) continue;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
        decrementActiveThreads();
    }
}

void ThreadPool::incrementActiveThreads() {
    activeThreads++;
}

void ThreadPool::decrementActiveThreads() {
    activeThreads--;
}

int ThreadPool::getActiveThreads() const {
    return activeThreads.load();
}

int ThreadPool::getMaxThreads() const
{
    return maxThreads;
}

std::mutex& ThreadPool::getMtx()
{
    return mtx;
}
