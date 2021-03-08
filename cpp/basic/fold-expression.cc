#include <iostream>


template<typename... Args>
void display(Args... args)
{
    (std::cout << ... << args) << " ";
}

