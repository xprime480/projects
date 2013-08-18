
#include <iostream>

#include "Utils.h"
#include "Products.h"

Product::Product()
{
  Key = ++KeySource;
  // random_value(Q0, -1.0, 5.0);
  // random_value(beta, 0.0, 4.0);
  random_value(rateMin, 400, 900);
  rateMax = rateMin + NumRates - 1;
  random_value(rateOptPrior, rateMin, rateMax);

  double o = -100000000;
  // std::cerr << "*******************\n";
  for ( int r = rateMin ; r <= rateMax ; ++r ) {
    double obj = computeObjective(r); 
    objectives[r] = obj;

    // std::cerr << "\n";
    if ( obj > o ) {
      o = obj;
      rateOpt = r;
    }
  }
}

void Product::report() const
{
  std::cerr << "Key = " << getKey() << "; Rate = " << getOptRate()
	    << "; min = " << getMinRate()
	    << "; max = " << getMaxRate()
	    << "\n";
#if 0
  std::cerr << "\tq0 = " << Q0 << "; beta = " << beta
	    << "; objective = " << objective(getOptRate()) << "\n";
#endif
}

double Product::objective(int Rate) const
{
  if ( Rate < rateMin ) {
    throw "Product::objective: Rate too low\n";
  }
  if ( Rate > rateMax ) {
    throw "Product::objective: Rate too high\n";
  }
  return objectives[Rate];
}

int Product::getMinRate() const
{
  return rateMin;
}

int Product::getMaxRate() const
{
  return rateMax;
}

int Product::getOptRate() const
{
  return rateOpt;
}

int Product::getKey() const
{
  return Key;
}

double Product::computeObjective(int Rate) const
{
#if 0
  double profit = Rate - 550;
  double volume = std::exp(Q0 - beta * (Rate / 10000.0));
  double obj    = profit * volume + 1000 * volume;
#else
  double delta  = Rate - rateOptPrior;
  double obj    = -1.0 * delta * delta;
#endif
  // std::cerr << " [p " << profit << " v " << volume << " o " << obj << " ] ";
  return obj;
}

int Product::KeySource(0);
