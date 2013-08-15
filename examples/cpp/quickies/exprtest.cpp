
#include <iostream>
#include <iomanip>

using namespace std;

int main(int, char **)
{
  cout << hex << (- (1 | 2)) << endl;
  cout << hex << ((- 1) | 2) << endl;
  cout << hex << (- 1) << endl;
  
  return 0;
}
