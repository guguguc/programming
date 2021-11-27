#include "../utils.h"
#include <iostream>
#include <string>

using namespace std;

class A {
public:
    A(): A(0) { }
    explicit A(int a): m_name(a) { Utils::print("ctor: A"); }
    virtual void disp1() const { Utils::print("Virtual: this is A"); }
    void disp2() const { Utils::print("Non-Virtual: This is A"); }
    virtual ~A() { Utils::print("dtor: A"); };
public:
    int m_name;
};

class A1 : public A {
public:
    A1(): A(), arr(nullptr) { Utils::print("ctor: A1"); }
    A1(int a, int len) : A(a), arr(new int[len]) { Utils::print("ctor: A1"); }
    virtual void disp1() const override { Utils::print("Virtual: This is A1"); }
    void disp2() const { Utils::print("Non-Virtual: This is A1"); }
    ~A1() override { Utils::print("dtor: A1"); if(arr) delete arr; }
public:
    int *arr;
};
