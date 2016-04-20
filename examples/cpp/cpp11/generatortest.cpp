
#include <iostream>
#include <set>
#include <map>
#include <string>

#include "range.h"
#include "streamutils.h"
#include "containerstream.h"

using std::cout;
using std::endl;
using std::set;
using std::map;
using std::string;

void generatortest()
{
  Range<int> basic(1,13,1);

  {
    auto t = basic;
    dump_stream(t);
  }
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
