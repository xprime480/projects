#if ! defined(GeneralizedFibonacci_h)
#define GeneralizedFibonacci_h 1

#include "LazySeq.h"

/**
 * GeneralizedFibonacci
 *
 * This class lazily builds an infinite sequence from two values.
 * Each new value in the output is the sum of two preceding values.
 * 
 * Examples:
 *  1 + 1 -> (1 1 2 3 5 8 ...)
 *  3 + 2 -> (3 2 5 7 12 19 ...)
 *
 */
template <typename T = int>
class GeneralizedFibonacci : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param _a The first value of the sequence
   * @param _b The second value of the sequence
   */
  GeneralizedFibonacci(T _a, T _b)
    : LazySeq<T>(_a, false)
    , a(_a)
    , b(_b)
  {
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    LazySeq<T> * z = NULL;
    if ( this->empty ) {
      z = new NullSeq<T>();
    }
    else {
      z = new GeneralizedFibonacci<T>(b, a+b);
    }

    TRACEALLOC(z);
    return z;
  }

private:
  T a;				// the current value
  T b;				// the next value
};

#endif // not defined GeneralizedFibonacci_h
