
#include <iostream>
#include <utility>
#include <cmath>

#include "ExpSolver.h"
#include "ExponentialGenerator.h"
#include "UniformGenerator.h"

static const int NNN = 1000000;
static UniformGenerator ugen(0, NNN);

using namespace std;

ExponentialGenerator::ExponentialGenerator(int _min, int _max, int _half)
  : min(_min)
  , max(_max)
  , half(_half)
  , cdf(max+1, 0.0)
{
  prepareCDF();
}

int ExponentialGenerator::gen()
{
  double x = double(ugen.gen()) / double(NNN);
  for ( int i = min ; i < max ; ++i ) {
    if ( x <= cdf[i] ) {
      return i;
    }
  }

  return max;
}

void ExponentialGenerator::prepareCDF()
{
  pair<double, double> ans = solve(max, half);
  double p = ans.first;
  double r = ans.second;
  double sum = 0.0;

  for ( int i = min ; i <= max ; ++i ) {
    double & v = cdf[i];
    sum += p * pow(r, (double) (i-1));
    v = sum;
  }

  for ( int i = min ; i <= max ; ++i ) {
    double & v = cdf[i];
    v /= sum;
  }
}


