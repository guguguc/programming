#include <fmt/core.h>
#include <string>

struct A {
    A() : A(0, 0) {}
    A(int a1, int a2) : m_a1(a1), m_a2(a2) {}
    int m_a1, m_a2;
private:
    char m_a3[10];
};

struct B : A{
    using A::A;
    int m_b1, m_b2;
};

template<typename T, typename U>
int offset_of(T U::*member)
{
    U *p = 0;
    return reinterpret_cast<int>(&(p->*member));
}

int main()
{
    std::string tmp("offset of {}: {}\n");
    fmt::print(tmp, "A::m_a1", offset_of(&A::m_a1));
    fmt::print(tmp, "B::m_b1", offset_of(&B::m_b1));
}
