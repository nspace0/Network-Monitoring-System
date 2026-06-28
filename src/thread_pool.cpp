#include "../include/thread_pool.hpp"

#include <stdexcept>

ThreadPool::ThreadPool(std::size_t threads) {
    for (std::size_t i = 0; i < threads; ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock lock(mutex);

                    cv.wait(lock, [this]() { return stop || !tasks.empty(); });

                    if (stop && tasks.empty()) return;

                    task = std::move(tasks.front());
                    tasks.pop();

                    ++active_tasks;
                }

                task();

                {
                    std::lock_guard lock(mutex);

                    --active_tasks;

                    if (tasks.empty() && active_tasks == 0)
                        finished_cv.notify_all();
                }
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard lock(mutex);
        stop = true;
    }

    cv.notify_all();

    for (auto& worker : workers) worker.join();
}

void ThreadPool::Enqueue(std::function<void()> task) {
    {
        std::lock_guard lock(mutex);

        if (stop) throw std::runtime_error("ThreadPool stopped");

        tasks.push(std::move(task));
    }

    cv.notify_one();
}

void ThreadPool::Wait() {
    std::unique_lock lock(mutex);

    finished_cv.wait(lock,
                     [this]() { return tasks.empty() && active_tasks == 0; });
}