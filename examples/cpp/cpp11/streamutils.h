#if ! defined(STREAMUTILS_H)
#define STREAMUTILS_H 1

#include "generator.h"

template <typename T, typename U>
struct Taker : public Generator<T>
{
  Taker(size_t _n, U _gen)
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
  U gen;
};

template <typename U>
auto take(size_t n, U gen) -> Taker<decltype(gen()), U>
{
  using Q = decltype(gen());
  return Taker<Q, U>(n, gen);
}

template <typename T, typename U>
struct Dropper : public Generator<T>
{
  Dropper(size_t _n, U _gen)
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
  U gen;
};

template <typename U>
auto drop(size_t n, U gen) -> Dropper<decltype(gen()), U>
{
  using Q = decltype(gen());
  return Dropper<Q, U>(n, gen);
}

template <typename T, typename F, typename U>
struct Filterer : public Generator<T>
{
  Filterer(F _pred, U _gen)
    : pred(_pred)
    , gen(_gen)
  {
  }

  T operator()()
  {
    for ( ;; ) {
      T t = gen();
      if ( pred(t) ) {
	return t;
      }
    }
  }

private:
  F pred;
  U gen;
};

template <typename F, typename U>
auto filter(F pred, U gen) -> Filterer<decltype(gen()), F, U>
{
  using Q = decltype(gen());
  return Filterer<Q, F, U>(pred, gen);
}

template <typename T, typename F, typename U>
struct Whiler : public Generator<T>
{
  Whiler(F _pred, U _gen)
    : pred(_pred)
    , gen(_gen)
  {
  }

  T operator()()
  {
    T t = gen();
    if ( pred(t) ) {
      return t;
    }
    else {
      throw GeneratorException();
    }
  }

private:
  F pred;
  U gen;
};

template <typename F, typename U>
auto takewhile(F pred, U gen) -> Whiler<decltype(gen()), F, U>
{
  using Q = decltype(gen());
  return Whiler<Q, F, U>(pred, gen);
}





#endif
