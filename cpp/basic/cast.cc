#include <iostream>

using namespace std;

struct A{
    A(int a): a(a) { cout << "ctor: A\n"; }
    virtual void disp() { cout << "this is A\n"; }
    int a;
    ~A() {cout << "dtor: destructor!\n"; }
};

struct B: A {
    B(int a, int c = 0): A(a), c(c) { cout << "ctor: B\n"; };
    virtual void disp() { cout << "this is B\n"; }
    int c;
};

void echo(A &a)
{
    a.disp();
}

int main()
{
    int i = 10;
    double j;
    void *p;
    B sb(20);

    echo(sb);

    // static cast
    // j = static_cast<double>(i);
    // p = static_cast<void*>(&i);
    // cout << *static_cast<int*>(p) << "\n";
    // cout << sizeof(A) << "\n";
    // dynamic cast
    // const cast
    // reinterpret_cast
    return 0;
}
