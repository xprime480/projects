
#include <iostream>
#include <limits>

#include "Products.h"
#include "Particle.h"
#include "Swarm.h"



Swarm::Swarm(Product * products_, int pcount, int scount)
  : products(products_)
  , count(pcount)
  , position_max(new double[pcount])
  , objective_max(-std::numeric_limits<double>::max())
  , pp(products, count)
{
  swarm.reserve(scount);
  for ( int i = 0 ; i < scount ; ++i ) {
    Particle * p = new Particle(pp);
    swarm.push_back(p);
    p->update(position_max, objective_max);
  }
}

Swarm::~Swarm()
{
  double scount = swarm.size();
  for ( int i = 0 ; i < scount ; ++i ) {
    delete swarm[i];
  }
  delete [] position_max;
}

void Swarm::iterate(int maxPass, int stable, bool dump)
{
  int noChange = 0;
  for ( int i = 0 ; i < maxPass ; ++i ) {
    double omax = objective_max;
    if ( dump ) { 
      std::cerr << "pass " << (i+1) << "\n";
    }
    next();
    if ( dump ) {
      report();
    }
    if ( omax == objective_max ) {
      ++noChange;
      if ( noChange >= stable ) {
	break;
      }
    }
    else {
      noChange = 0;
    }
  }
}

void Swarm::next()
{
  double scount = swarm.size();
  for ( int i = 0 ; i < scount ; ++i ) {
    swarm[i]->next(position_max, pp);
  }
  for ( int i = 0 ; i < scount ; ++i ) {
    swarm[i]->update(position_max, objective_max);
  }
}


void Swarm::report() const
{
  double scount = swarm.size();
  for ( int i = 0 ; i < scount ; ++i ) {
    swarm[i]->report();
  }
  for ( int i = 0 ; i < count ; ++i ) {
    std::cerr << "Key = " << products[i].getKey()
	      << "; rate = " << (int) (0.5 + position_max[i]) << "\n";
  }
  std::cerr << "omax = " << objective_max << "\n";
  std::cerr << "**********************\n";
}
