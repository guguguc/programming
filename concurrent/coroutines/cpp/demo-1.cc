#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int block_io(size_t delay)
{
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    return 10;
}

const char* get_time()
{
    std::time_t t = std::time(nullptr);
    return std::asctime(std::localtime(&t));
}

int main()
{
    /* About future.
     * You get a future obj that allows you to check the task status and result
     * when you call particular function like:
     * 1. task.get_future()
     * 2. promise.get_future()
     * 3. std::async(launch_policy, func, args)
     * 4. co_return expression
     * Then you can call future.wait() to wait task to complete.
     * Or call future.get() to get return value directly.
     */
    size_t delay = 4;
    // future from a package_task
    std::cout << "create a future obj by packaged_task at " << get_time();
    std::packaged_task<int(size_t)> task(block_io);
    std::future<int> f1 = task.get_future();
    std::thread t(std::move(task), delay);
    // future from an async()
    std::cout << "create a future obj by std::async at " << get_time();
    std::future<int> f2 = std::async(std::launch::async, block_io, delay);
    // std::this_thread::sleep_for(std::chrono::seconds(8));
    std::cout << "wait the result of the future at " << get_time();
    f1.wait();
    f2.wait();
    std::cout << "Done at " << get_time()
              << "Result is " << f1.get() << ' ' << f2.get() << std::endl;
    t.join();
    return 0;
}
