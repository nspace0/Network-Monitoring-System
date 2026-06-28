#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    explicit ThreadPool(std::size_t threads);

    ~ThreadPool();

    void Enqueue(std::function<void()> task);

    void Wait();

private:
    std::vector<std::thread> workers;

    std::queue<std::function<void()>> tasks;

    std::mutex mutex;
    std::condition_variable cv;

    std::condition_variable finished_cv;

    bool stop = false;

    std::size_t active_tasks = 0;
};