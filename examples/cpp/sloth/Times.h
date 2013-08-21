#if ! defined(Times_h)
#define Times_h 1

#include "Form.h"
#include "LazySeq.h"

/**
 * AnonSeq
 *
 * This class lazily builds a sequence from another sequence, where
 * the terms of the output sequence are the terms from the input
 * sequence times a constant.
 * 
 * Examples:
 *  3 + () -> ()
 *  0 + (1 1 1) -> (0 0 0)
 *  3 + (1 2 3) -> (3 6 9)
 */
template <typename T = int>
class Times : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param _n   the constant by which to multiply the input sequence
   * @param _seq input sequence
   */
  Times(T _n, LazySeq<T> * _seq)
    : LazySeq<T>()
    , n(_n)
    , seq(_seq)
  {
    init();
  }

  Times(T _n, Sloth::Form const & _seq)
    : LazySeq<T>()
    , n(_n)
    , seq(_seq.getLazySeq())
  {
    init();
  }

  /**
   * destructor
   */
  virtual ~Times()
  {
    deref(seq);
    seq = 0;
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
      z = new Times<T>(n, seq->tail());
    }

    TRACEALLOC(z);
    return z;
  }

private:

  T n;				// constant
  LazySeq<T> * seq;		// sequence

  void init()
  {
    addref(seq);
    if ( seq && ! seq->empty ) {
      this->head = n * seq->head;
      this->empty = false;
    }
  }
};
#endif // not defined Times_h
