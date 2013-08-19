#if ! defined(Cons_h)
#define Cons_h 1

#include "LazySeq.h"

/**
 * Cons
 *
 * This class builds a sequence from a value and another sequence,
 * where the value is the head of the new sequence and the input
 * sequence is the tail of the new sequence.
 *
 * Examples:
 *  V + () -> (V)
 *  V + (1 2 3) -> (V 1 2 3)
 *
 * If the input sequence is not NULL, the instance holds a reference
 * to it.  head holds V.
 */
template <typename T = int>
class Cons : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param value the value to set as the head of the new sequence
   * @param _cdr  the sequence to set at the tail of the new sequence
   */
  Cons(T value, LazySeq<T> * _cdr)
    : LazySeq<T>(value, false)
    , cdr(_cdr ? _cdr : new NullSeq<T>())
  {
    if ( ! _cdr ) {
      TRACEALLOC(cdr);
    }
    addref(cdr);
  }

  /**
   * destructor
   */
  virtual ~Cons()
  {
    deref(cdr);
  }
  
  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    return cdr;
  }  

private:
  LazySeq<T> * cdr;		// tail of this sequence
};

#endif // not defined Cons_h
