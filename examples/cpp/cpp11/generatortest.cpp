
#include <iostream>

#include "range.h"
#include "streamutils.h"

using std::cout;
using std::endl;

template <typename T>
void dump_stream(T gen)
{
  static const char * WS = " ";

  try {
    while ( true ) {
      cout << gen() << WS;
    }
  }
  catch ( GeneratorException ex ) {
    cout << endl;
  }
}

void generatortest()
{
  Range<int> basic(1,13,1);

  dump_stream(basic);
  dump_stream(take(6, basic));
  dump_stream(drop(6, basic));
  dump_stream(take(2, drop(6, basic)));
  dump_stream(filter([] (int i) {return i%2 == 1;}, basic));
  dump_stream(take(2, drop(6, Range<double>(1.0,13.0,1.234))));
  dump_stream(take(3, [] () { return "cat"; }));
  int x = 10;
  auto p = [x] (int i) {return i < x;};
  x = 0;
  dump_stream(takewhile(p, basic));
}
