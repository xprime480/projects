#if ! defined(LazySeqUtils_h)
#define LazySeqUtils_h 1

#include <cstdlib>
#include <sstream>
#include <string>

#include "Counter.h"
#include "LazySeq.h"
#include "MinMaxer.h"
#include "Taker.h"

/**
 * LazySeqUtils
 *
 * Some utilties for operating on lazy sequences.
 */
template <typename T = int>
class LazySeqUtils
{
public:
  /**
   * count
   *
   * count the number of items in a sequence.
   *
   * @param seq the input sequence
   *
   * @return the number of items in the sequence.
   */
  static size_t count(LazySeq<T> * seq)
  {
    LazySeq<T> * z = new Counter<T>(seq);
    TRACEALLOC(z);
    LazySeqStat::addref(z);
    size_t r = (size_t) z->head;
    LazySeqStat::deref(z);
    return r;
  }

  /**
   * print
   *
   * print the items to the standard output, separated by spaces.
   *
   * @param seq the input sequence
   */
  static void print(LazySeq<T> * seq)
  {
    LazySeqStat::addref(seq);

    while ( seq && ! seq->empty ) {
      cout << seq->head << " ";
      seq = LazySeq<T>::cdr(seq);;
    }
    cout << endl;

    LazySeqStat::deref(seq);
  }

  /**
   * minmax
   *
   * Convert a sequence into another sequence.  If the input is empty,
   * then so is the output.  Otherwise, the output is a two item
   * sequence (min_input max_output)
   *
   * @param seq the input sequence
   *
   * @return the output sequence
   */
  static LazySeq<T> * minmax(LazySeq<T> * seq)
  {
    LazySeq<T> * z = new MinMaxer<T>(seq);
    TRACEALLOC(z);
    return z;
  }

  /**
   * take
   *
   * Convert an input sequence into an output sequence which is a
   * prefix of the input.
   *
   * @param seq   the input sequence
   * @param count how many items to include in the output
   */
  static LazySeq<T> * take(LazySeq<T> * seq, size_t count)
  {
    LazySeq<T> * z = new Taker<T>(seq, count);
    TRACEALLOC(z);
    return z;
  }

};

#endif // not defined LazySeqUtils_h
