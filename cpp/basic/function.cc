#include <functional>

using namespace std;

int add(int x, int y) { return x + y; }

int main()
{
  // function
  int (*fp1)(int, int) = add;
  typedef int (*fptr)(int, int);
  fptr fp2 = add;

  // function object
  function<int(int, int)> f1 = add;
  using std::placeholders::_1;
  function<int(int, int)> f2 = bind(add, 10, _1);
  function<int(int, int)> f3 = [](int x, int y) { return x + y; };

  return 0;
}
