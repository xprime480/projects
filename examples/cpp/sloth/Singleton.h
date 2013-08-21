#if ! defined(Singleton_h)
#define Singleton_h 1

#include "RepeatSeq.h"

/**
 * RepeatSeq
 *
 * This class lazily builds a sequence from a value.  The sequence
 * contains exactly one instance of the value
 * 
 * Examples:
 *  2 -> (2)
 */

template <typename T = int>
class Singleton : public RepeatSeq<T>
{
public:
  /**
   * constructor
   *
   * @param value  the value to repeat
   */
  Singleton(T value)
    : RepeatSeq<T>(value, 1)
  {
  }

private:
};

#endif // not defined Singleton_h
