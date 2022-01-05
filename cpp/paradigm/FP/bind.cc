#include <functional>
#include <string>
#include <iostream>

using namespace std::placeholders;

class A
{
public:
    void echo(const std::string &strMsg)
    {
        std::cout << strMsg << "\n";
    }
};

template<typename T>
auto add(const T& a, const T& b) -> decltype(a+b)
{
    return a + b;
}

int main()
{

    A a;
    auto lam_func = [] (int a, int b) { return a + b; };
    auto mem_func_ = std::bind(&A::echo, &a, _1);
    auto nor_func_ = std::bind(add<int>, _1, 1);
    auto lam_func_ = std::bind(lam_func, _2, _1);

    return 0;
}
