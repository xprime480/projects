#if ! defined(Merge_h)
#define Merge_h 1

#include "LazySeq.h"

/**
 * Merge
 *
 * This class lazily merges two sorted sequences into a new sequence.
 * 
 * Examples:
 *  () + () -> ()
 *  () + (1) -> (1)
 *  (1) + (2) -> (1 2)
 *  (2) + (1) -> (1 2)
 */
template <typename T = int>
class Merge : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param a the first sequence
   * @param b the second sequence
   */
  Merge(LazySeq<T> * a, LazySeq<T> * b)
    : LazySeq<T>()
    , min(0)
    , max(0)
  {
    addref(a);
    addref(b);

    if ( (! a || a->empty) && (! b || b->empty) ) {
      this->empty = true;
    }
    else if ( (! a || a->empty) ) {
      LazySeq<T> * z = new NullSeq<T>();
      TRACEALLOC(z);
      setValues(b, z);
    }
    else if ( (! b || b->empty) ) {
      LazySeq<T> * z = new NullSeq<T>();
      TRACEALLOC(z);
      setValues(a, z);
    }
    else if ( a->head < b->head ) {
      setValues(a, b);
    }
    else {
      setValues(b, a);
    }

    deref(a);
    deref(b);
  }
  
  /**
   * destructor
   */
  ~Merge()
  {
    deref(min);
    deref(max);
    min = 0;
    max = 0;
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
    z = new Merge<T>(min->tail(), max);

    TRACEALLOC(z);
    return z;
  }

private:
  LazySeq<T> * min;		// the tail of the smaller input sequence
  LazySeq<T> * max;		// the larger input sequence

  /**
   * setValues
   *
   * Set the current sequence to be non-empty using the indicated
   * values
   *
   * @param less the input sequence whose head is smaller (or empty if
   *             both inputs are empty)
   * @param more the input sequence whose head is larger  (or empty)
   */
  void setValues(LazySeq<T> * less, LazySeq<T> * more)
  {
    this->head = less->head;
    min  = less;
    max  = more;
    addref(min);
    addref(max);
    this->empty = false;
  }
};

#endif // not defined Merge_h
