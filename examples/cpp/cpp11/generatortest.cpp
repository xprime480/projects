
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
  dump_stream(Range<int>(1,5,1));
  dump_stream(take(6, Range<int>(1,10000,1)));
  dump_stream(drop(6, Range<int>(1,13,1)));
  dump_stream(take(2, drop(6, Range<int>(1,13,1))));
  dump_stream(filter([] (int i) {return i%2 == 1;}, Range<int>(1,13,1)));
  dump_stream(take(2, drop(6, Range<double>(1.0,13.0,1.234))));
}
