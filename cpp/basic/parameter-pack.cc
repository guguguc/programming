#include <iostream>

template<typename T>
T add(T arg)
{
    return arg;
}

template<typename T, typename... Args>
T add(T arg1, Args ...args)
{
    return arg1 + add(args...);
}

/**
 * Use fold expression in C++17
 * add(1, 2, 3)
 * left  fold return ((1 + 2) + 3)
 * right fold return (1 + (2 + 3))
 */
template<typename T, typename... Args>
T add(Args ...args)
{
    std::cout << "use fold expression\n";
    return (... + args);
}


template<typename T>
T contor_pair(T arg)
{
    return arg;
}

template<typename T, typename... Args>
T contor_pair(T arg1, Args... args)
{
    T k = arg1 + contor_pair(args...);
    return (k * (k + 1)) + arg1;
}

int main()
{
    // std::cout << add<int>(1, 2, 3, 4);
    std::cout << contor_pair(1000, 1000, 10);
}
