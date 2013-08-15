#include <cmath>
#include <numeric>

#include "mathutils.h"

double round_gamma(double d)
{
  double dx = d * 100.0;
  double rx = fmod(dx,1.0);
  if ( rx > .000001 ) {
    dx -= rx;
    dx += 1;
  }
  else if ( -rx > .000001 ) {
    dx -= rx;
    dx -= 1;
  }
  return dx / 100.0;
}


