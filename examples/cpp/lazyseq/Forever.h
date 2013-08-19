#if ! defined(Forever_h)
#define Forever_h 1

#include "LazySeq.h"

/**
 * Forever
 *
 * This class lazily generates an infinite sequence consisting of
 * copies of a value.
 * 
 * Examples:
 *  V -> (V V V V ...)
 *
 */
template <typename T = int>
class Forever : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param value a value of which an infinite number of copies of
   *              which are injected into a sequence
   */
  Forever(T value)
    : LazySeq<T>(value, false)
  {
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    return this;
  }

private:
};

#endif // not defined Forever_h
