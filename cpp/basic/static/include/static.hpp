#ifndef __STATIC__
#define __STATIC__
#include <execinfo.h>
#include <iostream>

#define endl "\n"

void bt()
{
  const int sz = 20;
  void *arr[sz];
  char **bts;
  int size;
  size = backtrace(arr, sz);
  bts  = backtrace_symbols(arr, size);
  if (bts != nullptr) {
    std::cout << "frames: " << size << endl;
    for (int i = 0; i < size; ++i) {
      std::cout << bts[i] << endl;
    }
  } else {
      std::cout << "no frames!" << endl;
  }
  free(bts);
}

class A {
public:
  A() : m_a(0)
  {
    std::cout << __FUNCTION__ << endl;
  }
  A(int a) : m_a(a) {}
  ~A() { std::cout << __FUNCTION__ << endl; bt(); }
  int m_a;
};

#endif
