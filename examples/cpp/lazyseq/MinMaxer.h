#if ! defined(MinMaxer_h)
#define MinMaxer_h 1

#include "Cons.h"
#include "LazySeq.h"

using namespace std;

/**
 * MinMaxer
 *
 * This class greedily builds a lazy sequence from another sequence.
 * If the input sequence is empty, the output sequence is empty.
 * Otherwise, the output sequence has length 2 with the first element
 * being the minimum of all the inputs, and the second being the
 * minimum. 
 * 
 * Examples:
 *  () -> ()
 *  (1 1 1) -> (1 1)
 *  (4 1 3 2) -> (1 4)
 */
template <typename T = int>
class MinMaxer : public LazySeq<T>
{
public:
  /**
   * constructor
   *
   * @param src the sequence to scan
   */
  MinMaxer(LazySeq<T> * src)
    : LazySeq<T>()
  {
    if ( ! src || src->empty ) {
      return;
    }

    LazySeqStat::addref(src);

    this->empty = false;
    this->head = src->head;
    tval = src->head;
    src = LazySeq<T>::cdr(src);

    while ( src && ! src->empty ) {
      int v = src->head;
      this->head = min(this->head, v);
      tval = max(tval, v);
      src = LazySeq<T>::cdr(src);
    }

    LazySeqStat::deref(src);
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    LazySeq<T> * z = NULL ;
    if ( this->empty ) {
      z = new NullSeq<T>();
    }
    else {
      z = new Cons<T>(tval , NULL);
    }
    TRACEALLOC(z);
    return z;
  }

private:
  int tval;			// max val, i.e. the tail of the sequence
};

#endif // not defined MinMaxer_h
