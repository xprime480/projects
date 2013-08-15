
#include <iostream>

#include "TSP.h"

int main(int argc, char ** argv)
{
  if ( argc < 2 ) {
    std::cerr << "Usage: " << argv[0] << " problemfile\n";
    return 1;
  }

  TSP tsp;
  tsp.read(std::string(argv[1]) + ".in");
  tsp.solve();
  tsp.write(std::string(argv[1]) + ".out");

  return 0;
}
