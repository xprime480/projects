
#include <iostream>
#include <sstream>

using namespace std;

void f(int x) {}

int main(int, char **)
{
  stringstream s;
  s << "cat says " << 1 << " hahahaha";
  cout << s.str() << endl;

  return 0;
}
