#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <type_traits>
#include <vector>
#include <functional>
#include <future>

class ThreadPool {
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;

    bool stop;

public:
    ThreadPool(size_t threadCount);
    ~ThreadPool();

    // template<class F, class... Args>
    // auto enqueue(F&& f, Args&&... args)
    //     -> std::future<typename std::result_of_t<F(Args...)>::type>;
    void enqueue(std::function<void()> task);
};
