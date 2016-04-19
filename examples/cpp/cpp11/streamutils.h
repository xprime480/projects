#if ! defined(STREAMUTILS_H)
#define STREAMUTILS_H 1

#include "generator.h"

template <typename T>
struct Taker : public Generator<T>
{
  Taker(size_t _n, Generator<T> & _gen)
    : n(_n)
    , taken(0)
    , gen(_gen)
  {
  }

  T operator()()
  {
    if ( taken < n ) {
      ++taken;
      return gen();
    }
    throw GeneratorException();
  }

private:
  size_t n, taken;
  Generator<T> & gen;
};

template <typename T>
struct Dropper : public Generator<T>
{
  Dropper(size_t _n, Generator<T> & _gen)
    : gen(_gen)
  {
    for ( size_t dropped = 0 ; dropped < _n ; ++dropped ) {
      try {
	gen();
      }
      catch ( GeneratorException ex ) {
      }
    }
  }

  T operator()()
  {
      return gen();
  }

private:
  Generator<T> & gen;
};

#endif
