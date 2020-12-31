#include <thread>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

void spinner(int delay)
{
    string s = "-|/";
    for (int i = 0;; i=(i+1)%2) {
        std::cout << "\r" << s[i];
        std::cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

long long fib(int n)
{
    if (n < 2)
        return n;
    return fib(n-1) + fib(n-2);
}

int main()
{
    thread t(spinner, 100);
    t.detach();
    const int N = 50;
    long long ans = fib(N);
    std::cout << "\r" << "fib " << N << " is " << ans << "\n";

    return 0;
}
