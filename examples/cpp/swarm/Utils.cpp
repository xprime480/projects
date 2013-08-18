
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <algorithm>

#include "Utils.h"

void random_value(int & val, int min, int max)
{
  if ( max < min ) {
    std::swap( min, max );
  }
  else if ( min == max ) { 
    val = min;
    return;
  }

  val = min + rand() % (max - min);
  assert(val >= min && val <= max);
}

void random_value(double & val, double min, double max)
{
  if ( max < min ) {
    std::swap( min, max );
  }
  else if ( min == max ) { 
    val = min;
    return;
  }

  double const scale = 1000.0;
  double const tweak = 0.5 / scale;
  int tval;
  int tmin = (int) ((min + tweak) * scale);
  int tmax = (int) ((max - tweak) * scale);
  
  random_value(tval, tmin, tmax);
  val = (double) tval / scale;

  // correction for the errors that could be introduced by 
  // using the int scaling
  // 
  if ( val < min ) val = min;
  if ( val > max ) val = max;

  assert(val >= min && val <= max);
}
