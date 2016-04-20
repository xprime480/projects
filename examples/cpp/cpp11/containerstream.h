#if ! defined(CONTAINERSTREAM_H)
#define CONTAINERSTREAM_H 1

#include "generator.h"

template <typename C>
struct ContainerStream : Generator<typename C::value_type>
{
  using Iter = typename C::iterator;
  using T = typename C::value_type;

  ContainerStream(C & c)
    : beg(c.begin())
    , end(c.end())
  {
  }

  T operator()()
  {
    if ( beg == end ) {
      throw GeneratorException();
    }
    return *beg++;
  }

private:
  Iter beg, end;
};

#endif // CONTAINERSTREAM_H
