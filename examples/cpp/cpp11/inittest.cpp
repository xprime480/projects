
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Foo
{
  int x;
  string y;
  double z;
};

void inittest(int argc, char ** argv)
{
  using Data = vector<Foo>;
  
  const Data v = { 
    { 3, "cat", 7.55 }, 
    { 1, "hidden", -.13 }, 
    { 0, string(6, 'a'), 1.5e11 } 
  };

  cout << v.size() << endl;
  for ( const auto & f : v ) {
    cout << f.x << " " << f.y << " " << f.z << endl; 
  }
}
