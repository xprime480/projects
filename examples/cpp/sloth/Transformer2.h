#if ! defined(Transformer2_h)
#define Transformer2_h 1

#include "Form.h"

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
 *  [less] (2 2 2 2) (1 2 3 4) -> (0 0 1 1)
 */
template <typename _OP, typename T = int>
class Transformer2 : 
{
  typedef typename _OP::result_type U; // the base sequence type
public: 
  /**
   * constructor
   *
   * @param _s1 sequence for first operand
   * @param _s2 sequence for second operand
   */
  Transformer2(Form const & _f1, Form const & _f2)
    : LazySeq<T>()
    , seq1(_s1)
    , seq2(_s2)
  {
    init();
  }

  Transformer2(Sloth::Form const & _s1, Sloth::Form const & _s2)
    : LazySeq<T>()
    , seq1(_s1.getLazySeq())
    , seq2(_s2.getLazySeq())
  {
    init();
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
  virtual LazySeq<T> * tail()
  {
    LazySeq<T> * z = NULL;
    if ( this->empty ) {
      z = new NullSeq<T>();
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

  void init()
  {
    addref(seq1);
    addref(seq2);

    if ( ! seq1 || seq1->empty ) {
      return;
    }
    if ( ! seq2 || seq2->empty ) {
      return;
    }

    this->head = T(_OP()(seq1->head, seq2->head));
    this->empty = false;
  }
};

#endif // not defined Transformer_h
