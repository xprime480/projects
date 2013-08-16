
#include <iostream>

#include "util.h"
#include "ExpSolver.h"

using namespace std;

int main(int argc, char ** argv)
{
  --argc;
  ++argv;
  int max = getNumericArg(argc, argv, 20);
  if ( max <= 0 ) {
    max = 20;
  }
  int half = getNumericArg(argc, argv, max/3);;
  if ( half <= 0 ) {
    half = max/3;
  }

  pair<double, double> ans = solve(max, half);
  cout << ans.first << " " << ans.second << endl;
  return 0;
}
