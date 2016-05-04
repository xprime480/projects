#if ! defined(FIBONACCI_H)
#define FIBONACCI_H 1

#include "generator.h"

template<typename T = unsigned>
struct Fibonacci : public Generator<T>
{
  Fibonacci()
    : a(T{1})
    , b(T{1})
  {
  }

  T operator()()
  {
    T rv = a;
    T tmp = a+b;
    a = b;
    b = tmp;
    return rv;
  }

private:
  T a,b;
};

#endif /* FIBONACCI_H */
