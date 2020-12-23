#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*Fold expression*/
template<typename ... T>
auto add(const T& ... t)
{
    return (t + ...);
}

int main()
{
    cout << add(1, 2, 3) << "\n";
    vector v{1, 2, 3};
    cout << v[0];
    return 0;
}
