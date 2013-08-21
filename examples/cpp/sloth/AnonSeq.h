#if ! defined(AnonSeq_h)
#define AnonSeq_h 1

#include "Cons.h"
#include "Form.h"
#include "LazySeq.h"

/**
 * AnonSeq
 *
 * This class lazily builds a sequence from another sequence.  If the
 * input sequence is empty, the output sequence is empty.  Otherwise,
 * if the prefix of the input sequence is M copies of value V (where M
 * is the largest value for which the assertion is true), then the
 * output sequence is M, V, followed by the same transformation done
 * on the tail of the input.  
 * 
 * Examples:
 *  () -> ()
 *  (1 1 1) -> (3 1)
 *  (1 1 2 2 2 2) -> (2 1 4 2)
 *
 * If the sequence is not empty, then head holds M, tail()->head holds
 * V, and tail()->tail() lazily computes the remainder of the sequence.
 */
template <typename T = int>
class AnonSeq : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param src the source sequence for the transformation
   *            The source is read up to the point where the value
   *            changes, and a reference is kept for the tail of the
   *            sequence.
   */
  AnonSeq(LazySeq<T> * src)
    : LazySeq<T>()
    , source(src)
  {
    init();
  }

  AnonSeq(Sloth::Form const & src)
    : LazySeq<T>()
    , source(src.getLazySeq())
  {
    init();
  }

  /**
   * destructor
   *
   * Release the reference to the source sequence.
   */
  virtual ~AnonSeq()
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
    if ( this->empty ) {
      LazySeq<T> * z = new NullSeq<T>();
      TRACEALLOC(z);
      return z;
    }

    LazySeq<T> * y = new AnonSeq<T>(source);
    TRACEALLOC(y);
    addref(y);
    LazySeq<T> * z = new Cons<T>(value, y);
    deref(y);
    TRACEALLOC(z);
    return z;
  }
  
private:
  LazySeq<T> * source;		// unused portion of the original sequence
  T value;			// value used from the original
				// sequence

  void init()
  {
    addref(source);
    if ( (! source) || source->empty ) {
      return;
    }

    T count = 1;
    value = source->head;
    source = cdr(source);

    while ( source && ! source->empty && source->head == value ) {
      ++count;
      source = cdr(source);
    }

    this->head = count;
    this->empty = false;
  }
};

#endif // not defined AnonSeq_h
