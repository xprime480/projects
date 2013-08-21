#if ! defined(Taker_h)
#define Taker_h 1

#include "Form.h"
#include "LazySeq.h"

/**
 * Taker
 *
 * This class lazily builds a sequence from an another sequence and an
 * integer value.  The first N items of the input are included in the
 * output and the rest, if any, is discarded.
 * 
 * Examples:
 *  () + 2 -> ()
 *  (1 2 3) + 2 -> (1 2)
 *  (1 2 3) + 4 -> (1 2 3)
 *  (1 1 2 2 2 2) + 4 -> (1 1 2 2)
 */
template <typename T = int>
class Taker : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param src the input sequence
   * @param n   the length of the prefix to use as the output sequence
   */
  Taker(LazySeq<T> * src, size_t n)
    : LazySeq<T>()
    , source(src)
    , max(n)
  {
    init();
  }

  Taker(Sloth::Form const & src, size_t n)
    : LazySeq<T>()
    , source(src.getLazySeq())
    , max(n)
  {
    init();
  }

  /**
   * destructor
   */
  virtual ~Taker()
  {
    deref(source);
    source = 0;
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
      z = new Taker<T>(source->tail(), max - 1);
    }

    TRACEALLOC(z);
    return z;
  }

private:
  LazySeq<T> * source;		// source sequence
  size_t max;			// maximum number to take

  void init()
  {
    addref(source);
    if ( source && (! source->empty) && (max > 0) ) {
      this->head = source->head;
      this->empty = false;
    }
    else {
      this->empty = true;
    }
  }
};

#endif // not defined Taker_h
