#if ! defined(GeneralizedHamming_h)
#define GeneralizedHamming_h 1

#include "LazySeq.h"
#include "Merge.h"
#include "Times.h"

/**
 * GeneralizedHamming
 *
 * This class lazily builds a sequence from another sequence.  If the
 * input sequence is empty, the output sequence is empty.  Otherwise,
 * the output is the sorted sequence of all integers that any of the
 * inputs as divisors.  
 *
 * The input is presumed sorted and relatively prime.  Odd results
 * ensue of these assumptions are not met.
 * 
 * Examples:
 *  () -> ()
 *  (2) -> (2 4 8 16 32 ...)
 *  (2 3) -> (2 3 4 6 8 9 12 ...)
 *  (6) -> (6 36 216 ...)  // the inputs do not have to be prime.
 *
 */
class GeneralizedHamming : public LazySeq<int>
{
public:
  /**
   * constructor
   *
   * @param gens the generators
   *
   */
  GeneralizedHamming(LazySeq<int> * gens);

  /**
   * destructor
   */
  virtual ~GeneralizedHamming();

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<int> * tail();

private:
  LazySeq<int> * generators;	// generator
};

#endif // not defined GeneralizedHamming_h
