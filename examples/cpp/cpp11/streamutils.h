#if ! defined(STREAMUTILS_H)
#define STREAMUTILS_H 1

#include <iostream>
#include <vector>

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
struct TakeWhiler : public Generator<T>
{
  TakeWhiler(F _pred, U _gen)
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
auto takewhile(F pred, U gen) -> TakeWhiler<decltype(gen()), F, U>
{
  using Q = decltype(gen());
  return TakeWhiler<Q, F, U>(pred, gen);
}

template <typename T, typename F, typename U>
struct DropWhiler : public Generator<T>
{
  DropWhiler(F _pred, U _gen)
    : pred(_pred)
    , gen(_gen)
    , first(true)
  {
  }

  T operator()()
  {
    if ( first ) {
      first = false;
      return skipvals();
    }
    return gen();
  }

private:
  F pred;
  U gen;
  bool first;

  T skipvals()
  {
    for ( ;; ) {
      T val = gen();
      if ( ! pred(val) ) {
	return val;
      }
    }
    return gen();  // should never execute
  }
};

template <typename F, typename U>
auto dropwhile(F pred, U gen) -> DropWhiler<decltype(gen()), F, U>
{
  using Q = decltype(gen());
  return DropWhiler<Q, F, U>(pred, gen);
}

template <typename T, typename U, typename V>
void process_stream(T && gen, U element_handler, V end_handler)
{
  try {
    while ( true ) {
      auto e = gen();
      element_handler(e);
    }
  }
  catch ( GeneratorException ex ) {
    end_handler();
  }
}

namespace std
{
  template<typename F, typename S, typename O>
  O & operator << (O & os, const pair<F, S> & p) 
  {
    return os << '<' << p.first << ": " << p.second << '>';
  }
}

template <typename T>
void dump_stream(T && gen)
{
  using E = decltype(gen());

  auto elem_handler = [] (E const & e) { std::cout << e << " "; };
  auto end_handler  = [] () { std::cout << std::endl; };

  process_stream(gen, elem_handler, end_handler);
}

template <typename T>
auto collect(T & gen) -> std::vector<decltype(gen())>
{
  using E = decltype(gen());
  std::vector<E> vec;

  auto elem_handler = [&vec] (E const & e) { vec.push_back(e); };
  auto end_handler  = [] () {};
  process_stream(gen, elem_handler, end_handler);

  return vec;
}



#endif
