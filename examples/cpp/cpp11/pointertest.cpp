
#include <map>
#include <memory>
#include <iostream>

#include "counted.h"

using std::cout;
using std::endl;
using std::map;
using std::shared_ptr;
using std::make_shared;

using SPC = shared_ptr<Counted>;
using MapType = map<int, SPC>;

MapType GlobalMap1;
shared_ptr<MapType> GlobalMap2;

void populate_GM1()
{
  auto del = [] (Counted * p) { cout << "special deleter" << endl; delete p; };
  SPC c2(new Counted(), del);
  SPC c3(new Counted());
  GlobalMap1[3] = c2;
  GlobalMap1[6] = c3;
}

void populate_GM2()
{
  GlobalMap2.reset(new MapType(GlobalMap1));
  {
    SPC c4(new Counted());
    SPC c5(new Counted());
    (*GlobalMap2)[3] = c4;
  }
}

void pointertest(int argc, char ** argv)
{
  SPC c1(new Counted());
  populate_GM1();
  populate_GM2();
  GlobalMap1.clear();
  GlobalMap2.reset();
}
