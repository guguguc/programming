#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

struct A;

struct C {
    C(): ptr() {cout << "construct C" << endl;};
    ~C() {cout << "[C]: delete ptr of A, A's ref count: "
               << ptr.use_count() << endl;};

    // shared_ptr<A> ptr;
    weak_ptr<A> ptr;
};

struct A {
    A(): ptr(new C()) {cout << "construct A" << endl;};
    virtual ~A() {cout << "[A]: delete ptr of C, C's ref count: "
                       << ptr.use_count()
                       << " A's ref count: " << ptr->ptr.use_count()
                       << endl;};

    shared_ptr<C> ptr;
};

struct B: public A {
    B() {cout << "construct B" << endl;};
    virtual ~B() {cout << "deletc B" << endl;};
};


void test_shared()
{
    shared_ptr<A> p = make_shared<A>();
    shared_ptr<A> q = p;
    assert(p.use_count() == q.use_count());
    p.reset();
    assert(p.use_count() == 0);
    assert(q.use_count() == 1);
    cout << "ref count of q:" << q.use_count() << "\n";
    // cycle ref if q->ptr->ptr is not weak_ptr
    q->ptr->ptr = q;
    cout << "ref count of q:" << q.use_count() << "\n";
    cout << "ref count of q->ptr:" << q->ptr.use_count() << "\n";
    cout << "q->ptr->ptr --> q\n";
    {
        auto r = q->ptr->ptr.lock();
        cout << "ref count of q:" << q.use_count() << "\n";
    }
}

void test_unique()
{
    cout << "\n";
    auto p = make_unique<A>();
    // auto q = p; assignment ctor is deleted
    // auto q(p);  copy ctor is deleted
    auto q = move(p);
    assert(!p);
}

void test_weak()
{
    cout << "\n";
    shared_ptr<int> p = make_shared<int>(10);
    weak_ptr<int> q = p;
    cout << "ref count of p:" << p.use_count() << "\n";
    cout << "ref count of q:" << q.use_count() << "\n";
    {
        auto r = q.lock();
        cout << "ref count of p:" << p.use_count() << "\n";
        cout << "ref count of q:" << q.use_count() << "\n";
    }
    p.reset();
    cout << "ref count of p:" << p.use_count() << "\n";
    cout << "q is expired? " << q.expired() << "\n";
}

void test_basic()
{
    test_shared();
    test_unique();
    test_weak();
}

int main()
{
    test_basic();
    return 0;
}
