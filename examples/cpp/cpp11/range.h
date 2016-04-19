
#include "generator.h"

struct RangeException : public GeneratorException {};

template<typename T>
struct Range : public Generator<T>
{
  Range(T l, T h, T s)
    : lo(l)
    , hi(h)
    , step(s)
  {
  }

  T operator()()
  {
    if ( lo >= hi ) 
      throw RangeException();
    T rv = lo;
    lo += step;
    return rv;
  }

private:
  T lo,hi,step;
};
