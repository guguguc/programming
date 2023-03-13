#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

class ThreadPool {
public:
  ThreadPool(size_t num_threads)
  {
    for (size_t i = 0; i < num_threads; ++i) {
      m_threads.emplace_back([this] {
        while (true) {
        //   std::cout << "looping...\n";
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cond.wait(lock, [this] { return !m_tasks.empty() || m_stop; });
            // std::cout << "tid: " << std::this_thread::get_id()
            //           << " has been notified\n";
            if (m_stop && m_tasks.empty()) {
              return;
            }
            task = std::move(m_tasks.front());
            m_tasks.pop();
            // std::cout << "start to do work\n";
          }
          task();
        }
      });
    }
  }

  ~ThreadPool()
  {
    // std::cout << "destroy...\n";
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_stop = true;
    }
    m_cond.notify_all();
    // std::cout << "start to join\n";
    for (auto &thread : m_threads) {
    //   std::cout << thread.get_id() << " start to join \n";
      thread.join();
    }
  }

  template <typename Func, typename... Args>
  auto enqueue(Func &&func, Args... args)
      -> std::future<decltype(func(args...))>
  {
    using return_type = decltype(func(args...));
    auto task         = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_tasks.emplace([task] {(*task)();});
    //   std::cout << "task queue size: " << m_tasks.size() << std::endl;
    }
    m_cond.notify_one();
    return res;
  }

private:
  std::vector<std::thread> m_threads;
  std::queue<std::function<void()>> m_tasks;
  std::mutex m_mutex;
  std::condition_variable m_cond;
  bool m_stop = false;
};