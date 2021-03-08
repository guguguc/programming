#include <iostream>
#include <utility>
#include <memory>

using namespace std;

struct A {
    A(int &i) { cout << "lvalue overloding!\n"; }
    A(int &&i) { cout << "rvalue overloading!\n"; }
};

template<class T, class U>
unique_ptr<T> make_unique1(U&& u)
{
    return unique_ptr<T>(new T(std::forward<U>(u)));
}

/**
 * Call lvalue overloading whether u is a lvalue or rvalue.
 */
template<class T, class U>
unique_ptr<T> make_unique2(U&& u)
{
    return unique_ptr<T>(new T(u));
}

int main()
{
    int i = 1;
    auto p1 = make_unique2<A>(i);
    auto p2 = make_unique2<A>(1);
    return 0;
}
