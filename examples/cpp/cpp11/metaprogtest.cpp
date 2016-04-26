
#include <iostream>
#include <type_traits>
#include <string>

using std::cout;
using std::endl;
using std::is_constructible;
using std::string;

template <typename T, bool useint, bool usenoarg>
struct DV
{
  static T get_default_value()
  {
    throw "No suitable default value";
  }
};

template <typename T, bool usenoarg>
struct DV<T, true, usenoarg>
{
  static T get_default_value()
  {
    static T value(0);
    return value;
  }
};

template <typename T>
struct DV<T, false, true>
{
  static T get_default_value()
  {
    static T value;
    return value;
  }
};

template <typename T>
T get_default_value()
{
  constexpr bool int_constr   = is_constructible<T, int>::value;
  constexpr bool noarg_constr = is_constructible<T>::value;

  return DV<T, int_constr, noarg_constr>::get_default_value();
}

struct Foo
{
  explicit Foo(string const & arg) {}
};

namespace std
{
  template <typename O>
  O & operator<< (O & os, Foo const &)
  {
    return os << "Foo";
  }
}

template <typename T>
void check_default(char const * type)
{
  try {
    T const t = get_default_value<T>();
    cout << "default " << type << " = <" << t << ">" << endl;
  }
  catch ( ... ) {
    cout << "no suitable default for " << type << endl;
  }
}

void metaprogtest()
{
  check_default<int>("int");
  check_default<double>("double");
  check_default<string>("std::string");
  check_default<Foo>("Foo");
}
