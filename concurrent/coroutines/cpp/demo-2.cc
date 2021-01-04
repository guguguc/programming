#include <coroutine>
#include <future>
#include <iostream>

using namespace std;

struct suspend_always {
    bool await_ready() noexcept
    {
        return false;
    }
    void await_resume() noexcept {}
    suspend_always() {}
};

std::future<unsigned> counter()
{
    cout << "coroutine about to suspend\n";
    for (unsigned i = 1;; ++i) {
        co_await i;
        cout << "coroutine to resume\n";
    }

}

int main()
{

    std::future<unsigned> f = counter();
    auto i = f.resume();
    cout << i << endl;
    i = f.resume()
    cout << i << endl;
    return 0;
}
