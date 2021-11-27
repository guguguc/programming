#include "class.h"

using namespace Utils;

int main()
{
    // stack
    {
        A1 a0(1, 1);
        // ctor: A
        // ctor: A1
        A a1 = a0;
        // ctor: A
        print(a1.m_name);
        // 1
        a1.disp1();
        // Virtual: This is A
        a1.disp2();
        // Non-Virtual: This is A
        // dtor: A
        // dtor: A1
        // dtor: A
    }

    print_seq();
    // size
    {
        // int + padding + vtptr(8) = 16
        print(sizeof(A));
        // 16 + 8 = 24
        print(sizeof(A1));
    }

    print_seq();
    // heap
    {
        A *a2 = new A1();
        // ctor: A
        // ctor: A1
        a2->disp1();
        // Virtual: This is A1
        a2->disp2();
        // Non-Virtual: This is A
        delete a2;
        // dtor: A1
        // dtor: A
    }

    return 0;
}
