
#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "Products.h"
#include "Swarm.h"

struct ProductReporter
{
  void operator()(Product const & p)
  {
    p.report();
  }
};

int main(int argc, char ** argv)
{
  srand(10023);			// constant for repeatability
  // srand(time(0));

  const int ProductCount = 100;
  const int SwarmCount   = 1000;
  const int PassCount    = 1000;
  const int StableCount  = 100;

  Product  products[ProductCount];
  Swarm    swarm(products, ProductCount, SwarmCount);

  swarm.report();
  swarm.iterate(PassCount, StableCount, !true);

  std::for_each(products, products + ProductCount, ProductReporter());

  std::cerr << "done\n";
}
