
#include <iostream>
#include <vector>

#include "range.h"
#include "streamutils.h"

using std::cout;
using std::endl;
using std::vector;

template <typename T, typename U, typename V>
void handle_stream(T gen, U element_handler, V end_handler)
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

template <typename T>
void dump_stream(T gen)
{
  using E = decltype(gen());

  auto elem_handler = [] (E const & e) { cout << e << WS; };
  auto end_handler  = [] () { cout << endl; };

  handle_stream(gen, elem_handler, end_handler);
}

template <typename T>
auto stream2vec(T gen) -> vector<decltype(gen())>
{
  using E = decltype(gen());
  vector<E> vec;

  auto elem_handler = [&vec] (E const & e) { vec.push_back(e); };
  auto end_handler  = [] () {};
  handle_stream(gen, elem_handler, end_handler);

  return vec;
}

void generatortest()
{
  Range<int> basic(1,13,1);
  Range<double> floaty(1.0,13.0,1.234);

  dump_stream(basic);
  dump_stream(take(6, basic));
  dump_stream(drop(6, basic));
  dump_stream(take(2, drop(6, basic)));
  dump_stream(filter([] (int i) {return i%2 == 1;}, basic));
  dump_stream(take(2, drop(6, floaty)));
  dump_stream(take(3, [] () { return "cat"; }));
  int x = 10;
  auto p = [x] (int i) {return i < x;};
  x = 0;
  dump_stream(takewhile(p, basic));
  dump_stream(dropwhile(p, basic));

  auto v = stream2vec(basic);
  cout << v.size() << endl;
}
