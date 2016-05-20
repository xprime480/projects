
#include <iostream>
#include <string>

#include "default_values.h"

using std::cout;
using std::endl;
using std::string;

struct Foo
{
  static string const unspecified;
  explicit Foo(string const & arg = unspecified) : name(arg) {}
  string name;
};
string const Foo::unspecified{ "generic Foo" };

namespace std
{
  template <typename O>
  O & operator<< (O & os, Foo const & f)
  {
    return os << f.name;
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

void metaprogtest(int argc, char ** argv)
{
  check_default<int>("int");
  check_default<double>("double");
  check_default<string>("std::string");
  check_default<Foo>("Foo");
}
