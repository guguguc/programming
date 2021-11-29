#include <iostream>
#include <string>
#include <vector>
#include <cassert>

void scref(const std::string &str)
{
  std::cout << "scref(const std::string&) " << str << "\n";
}

void scref(const std::string &&str)
{
  std::cout << "scref(const std::string&&) " << str << "\n";
}

void sref(std::string &str)
{
  std::cout << "sref(std::string&) " << str << "\n";
}

void sref(std::string &&str)
{
  std::cout << "sref(std::string&&) " << str << "\n";
}

int main() {
  // Declares a named var as a ref, that is,
  // an alias to an already-existing object or function
  // Note: refs are not objects; so
  // no arrays of ref,
  // no pointers to refs,
  // no refs to refs

  // Syntax
  // &  attr(opt) declarator (1)
  // && attr(opt) declarator (2)
  // (1) Lvalue ref declarator
  // (2) Rvalue ref declarator

  // Lvalue ref
  const char *a1 = "hello, word!";
  const char a2[] = "hello, word!";
  const char *&p1 = a1;
  const char(&p2)[13] = a2;

  // Rvalue ref
  // Used to extend the lifetimes of temp objects.
  // Lvalue to const can extend the lifetimes of temp objects,
  // but cannot modify them.
  std::string s1("test");
  // here (s1 + s1) is a temp string object.
  const std::string& s2 = s1 + s1;
  // wrong! error: can't modify ref to const
  // s2 += "test";
  // wrong! error: lvalue_ref_bind_to_temp
  // std::string& s3 = s1 + s1;
  std::string&& s3 = s1 + s1;
  s3 += "test";
  // Move out of an object in scope that is no longer needed.
  // here call move constructor of v2.
  std::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<int> v2(std::move(v1));
  assert(v1.empty());
  // std::move
  // used to indicate an object t may be "moved from"
  // allowing effient transfer of resource from t to anther object.

  // Forwarding references

  // Ref collapsing
  typedef int&  lref;
  typedef int&& rref;
  int n = 10;
  lref&  r1 = n;  // type of r1 is int&
  lref&& r2 = n;  // type of r2 is int&
  rref&  r3 = n;  // type of r3 is int&
  rref&& r4 = 1;  // type of r4 is int&&

  const std::string s4("cref");
  std::string s5("ref");
  std::string &s5_ = s5;
  scref(s4);
  scref("tmp str");
  sref(std::move(s5));
  std::cout << s5.size();

  return 0;
}
