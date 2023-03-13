#include "threadpool.hpp"
#include <list>
#include <string>
#include <sstream>

std::string func(std::string name)
{
    std::stringstream ss;
    ss << "name: " << name << " tid: " << std::this_thread::get_id();
    return ss.str();
}

int main()
{
    ThreadPool pool(8);
    std::list<std::future<std::string>> lst;
    std::vector<std::string> res;
    for (int i = 0; i < 16; ++i)
    {
        lst.emplace_back(pool.enqueue(func, std::to_string(i)));
    }
    while (res.size() != 16)
    {
        auto it = lst.begin();
        while (it != lst.end())
        {
            if (it->wait_for(0s) == std::future_status::ready)
            {
                res.emplace_back(it->get());
                it = lst.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    std::cout << "all finished\n";
    for (const auto &msg : res)
    {
        std::cout << msg << "\n";
    }


    return 0;
}