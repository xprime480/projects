
#include <unistd.h>
#include <iostream>
#include <cstdlib>

#include "Point.h"
#include "utils.h"

int main(int argc, char** argv)
{
  srand( time( 0 ) );

  unsigned MAX_STEPS = 100000;
  double MAX_DISTANCE = 1000.0;

  if ( argc > 1 ) {
    int temp = std::atoi(argv[1]);
    if ( temp > 0 ) {
      MAX_STEPS = temp;
    }
  }

  if ( argc > 2 ) {
    double temp = std::atof(argv[2]);
    if ( temp > 0 ) {
      MAX_DISTANCE = temp;
    }
  }

  Point p1;
  Point p2;

  double max_distance = 0.0;

  for ( unsigned int step = 0 ; step < MAX_STEPS ; ++step ) {
    double dist = distance(p1, p2);
    if ( dist > max_distance ) {
      max_distance = dist;
    }
    if ( dist < 0.0001 ) {
      std::cout << "converged at " << p1 << " on step " << step << std::endl;
    }
    if ( dist > MAX_DISTANCE ) {
      std::cout << "diverged at step " << step << std::endl;
      break;
    }

    p1 = p1.randomNeighbor();
    p2 = p2.randomNeighbor();
  }

  std::cout << "maximum distance was " << max_distance << std::endl;

}
