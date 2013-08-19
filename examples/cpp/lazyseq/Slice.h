
#include "LazySeq.h"

/**
 * Slice
 *
 * This class lazily builds an increasing range from a start value to
 * an end value, with a stride length.  The endpoint value is not
 * included in the range.
 * 
 * Examples:
 *  1 + 3 + 1 -> (1 2)
 *  3 + 1 + 1 -> ()
 *  1 + 10 + 3 -> (1 4 7)
 */
template <typename T = int>
class Slice : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param _start the first value (The sequence is empty if this
   *               value is >= the stop value)
   * @param _stop  one beyond the last value
   * @param _step  the increment between each value
   */
  Slice(T _start, T _stop, T _step = 1)
    : LazySeq<T>(_start, _start >= _stop)
    , start(_start)
    , stop(_stop)
    , step(_step)
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
      z = new Slice<T>(start+step, stop, step);
    }
    TRACEALLOC(z);
    return z;
  }

private:
  T start;
  T stop;
  T step;
};
