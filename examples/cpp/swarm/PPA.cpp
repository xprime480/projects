
#include <algorithm>
#include <cstdio>
#include <cassert>

#include "Utils.h"
#include "Products.h"
#include "PPA.h"


struct PPAtom
{
  double min, max;
  int index;
  Product * product;

  void reset();
};

void PPAtom::reset()
{
  min = product->getMinRate();
  max = product->getMaxRate();
}

struct PPSorter
{
  bool operator()(PPAtom const & a, PPAtom const & b)
  {
    return a.min < b.min;
  }
};

ParticlePositioner::ParticlePositioner(Product * products_, int pcount)
  : count(pcount)
  , ppa(new PPAtom[pcount])
  , indexer(new int[pcount])
{
  for ( int i = 0 ; i < count ; ++i ) {
    ppa[i].index = i;
    ppa[i].product = &products_[i];
    ppa[i].reset();
    indexer[i] = i;
  }
  std::sort(ppa, ppa + count, PPSorter());
}

ParticlePositioner::~ParticlePositioner()
{
  delete [] ppa;
  delete [] indexer;
}

int ParticlePositioner::getCount() const
{
  return count;
}

double ParticlePositioner::randomize(double * position)
{
  ppa_start();

  for ( int i = 0 ; i < count ; ++i ) {
    int index = indexer[i];
    PPAtom & atom = ppa[index];
    double value;
    random_value(value, atom.min, atom.max);
    atom.min = atom.max = value;
    propagate_bounds(index, value);
  }

  return ppa2obj(position);
}

double ParticlePositioner::update(double * position, double * velocity)
{
  ppa_start();

  for ( int i = 0 ; i < count ; ++i ) {
    int index = indexer[i];
    PPAtom & atom = ppa[index];
    double value;
    int pindex = atom.index;

    value = position[pindex] + velocity[pindex];
    if ( value < atom.min ) { value = atom.min; }
    if ( value > atom.max ) { value = atom.max; }
    atom.min = atom.max = value;
    propagate_bounds(index, value);
  }

  return ppa2obj(position);
}

void ParticlePositioner::ppa_start()
{
  for ( int i = 0 ; i < count ; ++i ) {
    ppa[i].reset();
  }

  std::random_shuffle(indexer, indexer + count);
}

void ParticlePositioner::propagate_bounds(int index, double value)
{
  for ( int j = index+1 ; j < count ; ++j ) {
    if ( ppa[j].min >= value ) {
      break;
    }
    else {
      ppa[j].min = value;
      assert(ppa[j].min <= ppa[j].max);
    }
  }

  for ( int j = index-1 ; j >= 0 ; --j ) {
    if ( ppa[j].max <= value ) {
      break;
    }
    else {
      ppa[j].max = value;
      assert(ppa[j].min <= ppa[j].max);
    }
  }
}

double ParticlePositioner::ppa2obj(double * position)
{
  double obj = 0.0;
  for ( int i = 0 ; i < count ; ++i ) {
    PPAtom & atom = ppa[i];
    int index = atom.index;
    double rate = atom.min;
    position[index] = rate;
    obj += atom.product->objective((int) (0.5 + rate));
  }

  return obj;
}





