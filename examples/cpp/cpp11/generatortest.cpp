
#include <iostream>
#include <set>
#include <map>
#include <string>

#include "range.h"
#include "fibonacci.h"
#include "streamutils.h"
#include "containerstream.h"

using std::cout;
using std::endl;
using std::set;
using std::map;
using std::string;


template <typename T>
void takedroptest(T & t)
{
  {
    auto q = t;
    dump_stream(q);
  }
  dump_stream(take(6, t));
  dump_stream(drop(6, t));
  dump_stream(take(2, drop(6, t)));
  {
    auto odds = [] (int i) {return i%2 == 1;};
    dump_stream(filter(odds, t));
  }
  {
    Range<double> floaty(1.0,13.0,1.234);
    dump_stream(take(2, drop(6, floaty)));
  }
}

void conststreamtest()
{
  auto pigs = [] () { return "pig"; };
  dump_stream(take(3, pigs));
}

template <typename T>
void whiletest(T & t)
{
  int x = 10;
  auto p = [x] (int i) {return i < x;};
  dump_stream(takewhile(p, t));
  dump_stream(dropwhile(p, t));
}

template <typename T>
void collectortest(T & t)
{
  auto v = collect(t);
  cout << v.size() << endl;
}

void setdumptest()
{
  using type = set<int>;
  using ctype = ContainerStream<type>;

  type  s { 3, 1, 2, 6, 0, 3 };
  ctype c(s);
  dump_stream(c);
}

void mapdumptest()
{
  using type = map<string, int>;
  using ctype = ContainerStream<type>;

  type  s {
#include "name_to_code.txt"
  };
  ctype c(s);
  dump_stream(c);
}

void fibonaccitest()
{
  Fibonacci<> fibs;
  dump_stream(take(20, fibs));
}

void generatortest(int argc, char ** argv)
{
  Range<int> basic(1,13,1);

  takedroptest(basic);
  conststreamtest();
  whiletest(basic);
  collectortest(basic);
  setdumptest();
  mapdumptest();
  fibonaccitest();
}
