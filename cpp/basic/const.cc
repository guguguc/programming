#include <functional>
#include <iostream>
#include <vector>

using namespace std;

void func(const vector<int> &v) {
  cout << "called const func\n";
  for (auto &i : v)
    cout << i << endl;
}

void func(vector<int> &v) {
  cout << "called non-const func\n";
  for (auto &i : v)
    cout << i << endl;
}

int add(int x, int y) { return x + y; }

int main() {
  // const and non-const
  const vector<int> v1(10, 10);
  vector<int> v2(10, 10);
  func(v1);
  func(v2);

  // const pointer and pointer to const
  int i = 1;
  const int *p1 = nullptr;
  int *const p2 = nullptr;
  p1 = &i;
  *p2 = i;

}
