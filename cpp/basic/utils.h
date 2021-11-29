#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

namespace Utils {
    void print_seq()
    {
        std::cout << std::string(48, '-') << '\n';
    }

    template <typename T>
    void print(const T &val)
    {
        std::cout << val << '\n';
    }
}

#endif