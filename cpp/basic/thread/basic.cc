#include <thread>
#include <random>
#include <bits/stdc++.h>
#include <fmt/format.h>

#define FIXED_SIZE 1024

std::vector<int> vec(FIXED_SIZE);

uint64_t gen_num()
{
    static std::random_device rd;
    std::mt19937_64 gen(rd());
    return gen();
}

void init()
{
    std::transform(vec.begin(), vec.end(), vec.begin(), gen_num);
}


int main()
{
    init();
    for (auto item : vec)
    {
    }
    return 0;
}
