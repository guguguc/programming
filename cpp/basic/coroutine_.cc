#include <iostream>
#include <coroutine>

using namespace std;

auto hello()
{
    for (char ch: "hello, world!\n")
        co_yield ch;
}

int main()
{
    for (char ch: hello())
        cout << ch;
    return 0;
}
