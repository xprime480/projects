#if ! defined(Counter_h)
#define Counter_h 1

#include "LazySeq.h"

/**
 * Counter
 *
 * This class builds a singleton sequence from another sequence.  The
 * output is the length of the input.
 *
 * Examples:
 *  () -> (0)
 *  (1 2 1) -> (3)
 */
template <typename T = int>
class Counter : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param src the sequence whose elements are to be counted.
   */
  Counter(LazySeq<T> * src)
    : LazySeq<T>(0, false)
  {
    this->addref(src);
    while ( src && (! src->empty) ) {
      this->head += 1;
      src = this->cdr(src);
    }
    this->deref(src);
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    LazySeq<T> * z = new NullSeq<T>();
    TRACEALLOC(z);
    return z;
  }

private:
};

#endif // not defined Counter_h
