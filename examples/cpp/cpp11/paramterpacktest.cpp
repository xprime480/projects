#include <iostream>
#include <string>
#include <algorithm>

#include "sumsizes.h"
#include "rb.h"

using std::cout;
using std::endl;
using std::boolalpha;
using std::string;
using std::accumulate;

struct Foo
{
  int x;
  double y;
  int z;
};

class Master
{
public:
  template <typename... Ts>
  size_t f(Ts... args...)
  {
    return sumsizes<Ts...>::sum;
  }

  using vptr = void *;
  vptr aPtr, bPtr, cPtr;
};

template <typename... Ts>
void test()
{
  cout << sizeof...(Ts)
       << ": " << sumsizes<Ts...>::sum
       << ": " << RB<Ts...>::show() << endl;

  constexpr size_t N = sizeof...(Ts);

  size_t dummy1[N] = { sumsizes<Ts>::sum... };
  auto prod = [](size_t a, size_t b) { return a * b; };
  cout << accumulate(&dummy1[0], &dummy1[N], 1, prod) << endl;

  bool dummy2[N] = { (sumsizes<Ts>::sum > 0)... };
  auto all = [](bool a, bool b) { return a && b; };
  cout << boolalpha << accumulate(&dummy2[0], &dummy2[N], true, all) << endl;

  cout << endl;
}

void parameterpacktest()
{
  test<int, double, char>();
  test<int&, double&, char&>();
  test<Foo>();
  test<int>();
  test<void>();
  test<int, void, Foo, double, Foo, string, void>();

  Master m;
  cout << m.f(1, m) << endl;
}
