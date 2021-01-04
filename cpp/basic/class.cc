#include <iostream>

using namespace std;

class A {
public:
    // init data member by declaration
    // a = i + 1, b = i + 2, c = i + 3
    A(): a(0), b(0), c(0) {}
    A(int i): a(++i), c(++i), b(++i) {}
    A(char s): a(s), b(a), c(b) {}
    virtual void disp() { cout << "this is A\n"; }
    ~A();
public:
    int a;
    int b;
    int c;
};

A::~A()
{
    cout << "a:" << a << " " << "b:" << b << " " << "c:" << c << "\n";
    cout << "adr-a:" << &a << "\n"
         << "adr-b:" << &b << "\n"
         << "adr-c:" << &c << "\n";
}

class A1 : public A {
public:
    A1() = default;
    A1(int i) { a = b = c = i; }
    void disp() { cout << "this is A1\n"; }
};

int main()
{
    A1 a(10);
    A *p = &a;
    p->disp();
    return 0;
}
