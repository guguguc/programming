#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Object {
public:
  Object() = default;
  Object(size_t s) : container(s), size(s) {
    cout << "initial construct " << this << endl;
  };
  Object(Object &obj) : container(obj.container), size(obj.size) {
    cout << "copy construct " << this << endl;
  };
  Object(Object &&obj) noexcept
      : container(std::move(obj.container)), size(std::exchange(obj.size, 0)) {
    cout << "move construct " << this << endl;
  };
  ~Object() { cout << "destruct " << this << endl; };
  friend ostream& operator<<(ostream& os, const Object& obj);

public:
  vector<int> container;
  size_t size;
};

ostream& operator<<(ostream& os, const Object& obj)
{
    os << &obj;
    return os;
}

Object f(Object obj) { return obj; }

int main() {
  Object obj_1(10);
  cout << "Try to move\n";
  Object obj_2 = f(Object(10));
  cout << "Address of obj_2 is " << obj_2 << endl;
  cout << "Before move, obj_2.size is " << obj_2.size << endl;
  Object obj_3 = std::move(obj_2);
  cout << "after  move, obj_2.size is " << obj_2.size << endl;
  Object obj_4 = std::move(obj_1);
  Object obj_5(obj_4);
  return 0;
}
