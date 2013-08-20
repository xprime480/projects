#if ! defined(While2_h)
#define While2_h 1

#include "LazySeq.h"

/**
 * While2
 *
 * This class lazily builds a sequence from two other sequences.  The
 * length of the output is the lesser of the lengths of the two
 * inputs.  The first input sequence is a sequence of boolean values.
 * The output sequence consists of only those elements of the second
 * sequence whose corresponding element in the first sequence is
 * true.
 * 
 * Examples:
 *  () + (1 2 3) -> ()
 *  (true true false) + () -> ()
 *  (true false true) + (1 2 3) -> (1 3)
 */
template <typename T = int>
class While2 : public LazySeq<T>
{
public: 
  /**
   * constructor
   *
   * @param _cond selectors
   * @param _vals values
   */
  While2(LazySeq<bool> * _cond, LazySeq<T> * _vals)
    : LazySeq<T>()
    , cond(_cond)
    , vals(_vals)
  {
    LazySeqStat::addref(cond);
    this->addref(vals);

    if ( ! cond || cond->empty || ! vals || vals->empty ) {
      return;
    }

    if ( cond->head ) {
      this->head = vals->head;
      this->empty = false;
    }
  }

  /**
   * destructor
   */
  virtual ~While2()
  {
    LazySeqStat::deref(cond);
    this->deref(vals);
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
      z = new While2<T>(cond->tail(), vals->tail());
    }
    TRACEALLOC(z);
    return z;
  }

private:
  LazySeq<bool> * cond;		// selectors
  LazySeq<T> * vals;		// values
};

#endif // not defined While2_h
