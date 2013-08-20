#if ! defined(Appender_h)
#define Appender_h 1

#include "LazySeq.h"

/**
 * Appender
 *
 * This class lazily builds the concatentation of two sequences.  If
 * the first sequence is infinite, the second sequence is never
 * evaluated.
 *
 * Examples:
 *
 * () + ()  ->  ()
 * () + (a b c)  -> (a b c)
 * (a b c) + () -> (a b c)
 * (a b) + (c d) -> (a b c d)
 * (a b ...) + (c d) -> (a b ...)
 */

template <typename T = int>
class Appender : public LazySeq<T>
{
public: 
  /**
   * constructor
   *
   * @param _first  the first of the sequences to append.  A reference
   *                is kept to the input if it is not NULL
   * @param _second the second of the sequences to append.  A
   *                reference is kept to the input if it is not null.
   */
  Appender(LazySeq<T> * _first, LazySeq<T> * _second)
    : LazySeq<T>()
    , first(_first)
    , second(_second)
  {
    this->addref(first);
    this->addref(second);

    if ( first && ! first->empty ) {
      this->head = first->head;
      this->empty = false;
    }
    else if ( second && ! second->empty ) {
      this->head = second->head;
      this->empty = false;
    }
  }

  /**
   * destructor
   */
  virtual ~Appender()
  {
    this->deref(second);
    this->deref(first);
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
    else if ( first->empty ) {
      return second->tail();
    }
    else {
      z = new Appender<T>(first->tail(), second);
    }
    TRACEALLOC(z);
    return z;
  }

private:
  LazySeq<T> * first;
  LazySeq<T> * second;
};

#endif // not defined Appender_h
