#if ! defined(RepeatSeq_h)
#define RepeatSeq_h 1

#include "LazySeq.h"

/**
 * RepeatSeq
 *
 * This class lazily builds a sequence from a value and a repeat
 * count.
 * 
 * Examples:
 *  2 + 0 -> ()
 *  2 + 2 -> (2 2)
 */

template <typename T = int>
class RepeatSeq : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param value  the value to repeat
   * @param _count number of copies of the value in the sequence 
   */
  RepeatSeq(T value, size_t _count)
    : LazySeq<T>(value, _count == 0)
    , count(_count)
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
      z = new RepeatSeq<T>(this->head, count - 1);
    }
    TRACEALLOC(z);
    return z;
  }

private:
  size_t count;			// remaining count including the head
};

#endif // not defined RepeatSeq_h
