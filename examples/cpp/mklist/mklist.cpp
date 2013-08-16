
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

#include "util.h"
#include "ListMaker.h"


using namespace std;

void display(vector<int> & p)
{
}

int main(int argc, char** argv)
{
  ListMaker maker(--argc, ++argv);
  vector<int> p = maker.make();
  ostream_iterator<int> os(cout, " ");
  copy(p.begin(), p.end(), os);
  cout << endl;

  return 0;
}
