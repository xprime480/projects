
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

  auto r = Range<int>(1,10000,1);
  dump_stream(Taker<int>(6, r));

  auto s = Range<int>(1,13,1);
  dump_stream(Dropper<int>(6, s));
}
