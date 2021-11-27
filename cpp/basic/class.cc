#include <iostream>

using namespace std;

class A {
public:
    A(): m_a(0) {}
    explicit A(int a): m_a(a) {}
    virtual void disp1() { cout << __FUNCTION__ << " Virtual: this is A\n"; }
    void disp2() {cout << __FUNCTION__ << " This is A\n"; }
    virtual ~A() {cout << "dtor: A\n"; };
public:
    int m_a;
};

class A1 : public A {
public:
    A1(): A(), arr(nullptr) {}
    explicit A1(int a, int len) : A(a), arr(new int[len]) { cout << "new \n";}
    virtual void disp1() { cout << __FUNCTION__ << " Virtual: This is A1\n"; }
    void disp2() {cout << __FUNCTION__ << " This is A1\n"; }
    ~A1() { cout << "dtor: A1\n"; if(arr) delete arr; }
public:
    int *arr;
};

int main()
{
    cout << "non-pointer\n";
    {
        // A1调用A的默认构造函数
        A1 a0(1, 1);
        A a1 = a0;
        cout << a1.m_a << "\n";
        a1.disp1();
        a1.disp2();
        // new
        // dtor: A1
        // 1
        // Virtual: this is A
        // This is A
        // dtor: A   :a1 dtor
        // dtor: A1  :a0 dtor
        // dtor: A
    }
    /*
    cout << "\n";

    cout << "pointer\n";
    {
        A *a2 = new A1();
        a2->disp1();
        a2->disp2();
        delete a2;
    }
    */

    return 0;
}
