#include "class.h"
#include "../utils.h"

using namespace Utils;

int main()
{
    auto func_obj = [](const A &a) { a.disp1(); };
    auto func_pobj = [](const A *a) { a->disp1(); };

    // stack
    {
        A a1 = A1(1, 1);
        // ctor: A
        // ctor: A1
        // dtor A1
        // dtor A
        func_obj(a1);
        func_pobj(&a1);
        // Virtual: this is A
        // Virtual: this is A
        cout << sizeof(A) << endl;
        // 16
        // dtor: A
    }

    print_seq();
    // heap
    {
        A *a1 = new A1(1, 1);
        // ctor: A
        // ctor: A1
        func_obj(*a1);
        // Virtual: This is A1
        func_pobj(a1);
        // Virtual: This is A1
        delete a1;
        // dtor: A1
        // dtor: A
    }

    return 0;
}