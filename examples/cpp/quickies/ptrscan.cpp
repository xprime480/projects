
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
  int a,b,c;
  int * p[] = { &a, &b, &c, 0 };
  int ** end = find(p, p+8, (int *) 0);
  cout << distance(p, end) << endl;
  return 0;
}
