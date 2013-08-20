#if ! defined(Dropper_h)
#define Dropper_h 1

#include "LazySeq.h"

/**
 * Dropper
 *
 * This class lazily builds a sequence from an another sequence and an
 * integer value.  The first N items of the input are discarded and
 * the output consists of the remainder, if any.
 * 
 * Examples:
 *  () + 2 -> ()
 *  (1 2 3) + 2 -> (3)
 *  (1 2 3) + 4 -> ()
 *  (1 1 2 2 2 2) + 4 -> (2 2)
 *
 * head is computed greedily at construction time.  Tail is computed
 * lazily.  A reference is held the the non-dropped tail of the
 * sequence.
 */
template <typename T = int>
class Dropper : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param src The input sequence
   * @param n   The number of items to drop from the head of the input
   */
  Dropper(LazySeq<T> * src, size_t n)
    : source(src)
  {
    this->addref(source);
    while ( source && ! source->empty && n > 0 ) {
      source = this->cdr(source);
      --n;
    }

    if ( n > 0 ) {
      this->empty = true;
    }
    else {
      this->head = source->head;
      this->empty = false;
    }
  }

  /**
   * destructor
   */
  virtual ~Dropper()
  {
    this->deref(source);
    source = 0;
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    if ( this->empty ) {
      LazySeq<T> * z = new NullSeq<T>();
      TRACEALLOC(z);
      return z;
    }
    return source->tail();
  }

private:
  LazySeq<T> * source;		// tail of this sequence
};

#endif // not defined Dropper_h
