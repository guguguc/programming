#include <algorithm>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <vector>

void func(int i)
{
    std::cout << i << " thread id "
              << std::this_thread::get_id()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
}

int main()
{
  std::vector<std::thread> pool;
  for (int i = 0; i < 10; ++i) {
    pool.push_back(std::thread(func, i));
  }
  for (auto& p: pool)
      p.join();
  return 0;
}
