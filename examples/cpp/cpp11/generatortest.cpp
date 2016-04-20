
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

#include "range.h"
#include "streamutils.h"
#include "containerstream.h"

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::map;
using std::string;

template <typename T, typename U, typename V>
void process_stream(T gen, U element_handler, V end_handler)
{
  try {
    while ( true ) {
      auto e = gen();
      element_handler(e);
    }
  }
  catch ( GeneratorException ex ) {
    end_handler();
  }
}

const char * WS = " ";

namespace std
{
  template<typename F, typename S, typename O>
  O & operator << (O & os, pair<F, S> p) 
  {
    return os << '<' << p.first << ": " << p.second << '>';
  }
}

template <typename T>
void dump_stream(T gen)
{
  using E = decltype(gen());

  auto elem_handler = [] (E const & e) { cout << e << WS; };
  auto end_handler  = [] () { cout << endl; };

  process_stream(gen, elem_handler, end_handler);
}

template <typename T>
auto collect(T gen) -> vector<decltype(gen())>
{
  using E = decltype(gen());
  vector<E> vec;

  auto elem_handler = [&vec] (E const & e) { vec.push_back(e); };
  auto end_handler  = [] () {};
  process_stream(gen, elem_handler, end_handler);

  return vec;
}

void generatortest()
{
  Range<int> basic(1,13,1);

  dump_stream(basic);
  dump_stream(take(6, basic));
  dump_stream(drop(6, basic));
  dump_stream(take(2, drop(6, basic)));
  {
    auto odds = [] (int i) {return i%2 == 1;};
    dump_stream(filter(odds, basic));
  }
  {
    Range<double> floaty(1.0,13.0,1.234);
    dump_stream(take(2, drop(6, floaty)));
  }
  {
    auto pigs = [] () { return "pig"; };
    dump_stream(take(3, pigs));
  }
  {
    int x = 10;
    auto p = [x] (int i) {return i < x;};
    dump_stream(takewhile(p, basic));
    dump_stream(dropwhile(p, basic));
  }
  {
    auto v = collect(basic);
    cout << v.size() << endl;
  }

  {
    using type = set<int>;
    using ctype = ContainerStream<type>;

    type  s { 3, 1, 2, 6, 0, 3 };
    ctype c(s);
    dump_stream(c);
  }

  {
    using type = map<string, int>;
    using ctype = ContainerStream<type>;

    type  s {
#include "name_to_code.txt"
};
    ctype c(s);
    dump_stream(c);
  }
}
