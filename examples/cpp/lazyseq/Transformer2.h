#if ! defined(Transformer2_h)
#define Transformer2_h 1

#include "LazySeq.h"

/**
 * Transformer2
 *
 * This class lazily builds a sequence from two other sequences.  Part
 * of the template signature is the binary operation.  The length of
 * the output is the lesser of the lengths of the two inputs.
 * 
 * Examples:
 *  [multiplies] () + (1 2 3) -> ()
 *  [multiplies] (2 3 4) + (5 4 3) -> (10 12 12)
 *  [less] (2 2 2 2) (1 2 3 4) -> (false false true true)
 */
template <typename _OP, typename T = int>
class Transformer2 : public LazySeq<typename _OP::result_type>
{
  typedef typename _OP::result_type U; // the base sequence type
public: 
  /**
   * constructor
   *
   * @param _s1 sequence for first operand
   * @param _s2 sequence for second operand
   */
  Transformer2(LazySeq<T> * _s1, LazySeq<T> * _s2)
    : LazySeq<U>()
    , seq1(_s1)
    , seq2(_s2)
  {
    addref(seq1);
    addref(seq2);

    if ( ! seq1 || seq1->empty ) {
      return;
    }
    if ( ! seq2 || seq2->empty ) {
      return;
    }

    this->head = _OP()(seq1->head, seq2->head);
    this->empty = false;
  }

  /**
   * destructor
   */
  virtual ~Transformer2()
  {
    deref(seq1);
    deref(seq2);
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<U> * tail()
  {
    LazySeq<U> * z = NULL;
    if ( this->empty ) {
      z = new NullSeq<U>();
    }
    else {
      z = new Transformer2<_OP, T>(seq1->tail(), seq2->tail());
    }
    TRACEALLOC(z);
    return z;
  }

private:
  LazySeq<T> * seq1;		// first sequence
  LazySeq<T> * seq2;		// second sequence
};

#endif // not defined Transformer_h
