#if ! defined(NullSeq_h)
#define NullSeq_h 1

#include "LazySeq.h"



/**
 * NullSeq
 *
 * This class represents an empty sequence.
 * 
 * Examples:
 *   -> ()
 *
 */
template <typename T = int>
class NullSeq : public LazySeq<T>
{
public:
  /**
   * constructor
   */
  NullSeq()
    : LazySeq<T>()
  {
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
};

#endif // not defined NullSeq_h
