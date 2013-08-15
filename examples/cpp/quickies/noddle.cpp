
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <iterator>


using namespace std;

void randomize(vector<int> & p)
{
  random_shuffle(p.begin(), p.end());
}

void display(vector<int> & p)
{
  ostream_iterator<int> os(cout, "\n");
  copy(p.begin(), p.end(), os);
}


int main(int argc, char** argv)
{
  ++argv;
  --argc;
  size_t lim = 50;
  bool sorted = false;
  if ( argc > 0 && 0 == strcmp("-s", *argv) ) {
    sorted = true;
    --argc;
    ++argv;
  }
  if ( argc > 0 ) {
    lim = atoi(*argv);
    --argc;
    ++argv;
  }

  set<int> ns;

  if ( lim <= 10 ) {
    for ( int i = 1 ; i <= lim ; ++i ) {
      ns.insert(i);
    }
  }
  else {
    vector<double> pqrst(lim+1);
    srand(time(0));
  
    while ( ns.size() < 10 ) {
      int n = 1 + rand() % lim;
      pqrst[n] += 3.5;
      if ( pqrst[n] >= n ) {
	ns.insert(n);
      }
    }
  }

  vector<int> ls(ns.begin(), ns.end());
  if ( ! sorted ) {
    randomize(ls);
  }
  display(ls);

  return 0;
}
