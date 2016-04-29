#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::boolalpha;
using std::string;
using std::stringstream;
using std::accumulate;

template <typename T, typename... Ts>
struct sumsizes
{
  static constexpr size_t sum = sizeof(T) + sumsizes<Ts...>::sum;
};

template <typename T>
struct sumsizes<T>
{
  static constexpr size_t sum = sizeof(T);
};

template <typename... Ts>
struct sumsizes<void, Ts...>
{
  static constexpr size_t sum = sumsizes<Ts...>::sum;
};

template <>
struct sumsizes<void>
{
  static constexpr size_t sum = 0;
};

template <typename T, typename... Ts>
class RB : public RB<Ts...>
{
private:
  using my_base = RB<Ts...>;

public:
  static string show()
  {
    stringstream s;
    s << "(" << sizeof(T) << " " << my_base::show() << ")";
    return s.str();
  }
};

template <typename T>
class RB<T>
{
public:
  static string show()
  {
    stringstream s;
    s << "(" << sizeof(T) << ")";
    return s.str();
  }
};

template <typename... Ts>
class RB<void, Ts...> : public RB<Ts...>
{
private:
  using my_base = RB<Ts...>;

public:
  static string show()
  {
    stringstream s;
    s << "(" << my_base::show() << ")";
    return s.str();
  }
};

template <>
class RB<void>
{
public:
  static string show()
  {
    return "()";
  }
};

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
  test<int, double, int>();
  test<int&, double&, int&>();
  test<Foo>();
  test<int>();
  test<void>();
  test<int, void, Foo, double, Foo, string, void>();

  Master m;
  cout << m.f(1, m) << endl;
}
