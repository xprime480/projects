
#include <map>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::map;
using std::shared_ptr;
using std::make_shared

class C
{
public:
  C()
    : serial_number(++counter)
  {
    cout << "creating instance #" << serial_number << endl;
  }

  ~C()
  {
    cout << "deleting instance #" << serial_number << endl;
  }
private:
  int serial_number;
  static int counter;
};

int C::counter(0);

using SPC = shared_ptr<C>;
using MapType = map<int, SPC>;
using make_c = make_shared<C>

MapType GlobalMap1;
shared_ptr<MapType> GlobalMap2;

void populate_GM1()
{
  auto del = [] (C * p) { cout << "special deleter" << endl; delete p; };
  SPC c2(new C(), del);
  SPC c3(new C());
  GlobalMap1[3] = c2;
  GlobalMap1[6] = c3;
}

void populate_GM2()
{
  GlobalMap2.reset(new MapType(GlobalMap1));
  {
    SPC c4(new C());
    SPC c5(new C());
    (*GlobalMap2)[3] = c4;
  }
}

int main(int argc, char ** argv)
{
  SPC c1(new C());

  populate_GM1();
  populate_GM2();
  GlobalMap1.clear();
  GlobalMap2.reset();
  return 0;
}
