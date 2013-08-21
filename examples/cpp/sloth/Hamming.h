#if ! defined(Hamming_h)
#define Hamming_h 1

#include "GeneralizedHamming.h"

/**
 * Hamming
 *
 * This class lazily builds the Generalized Hamming sequence with
 * generators (2 3 5)
 * 
 * Examples:
 *  -> (2 3 4 5 6 8 ...)
 *
 */
class Hamming : public GeneralizedHamming
{
public:
  /**
   * constructor
   */
  Hamming();

protected:

private:
  /**
   * getGenerators
   *
   * Create the list of generators.
   *
   * @return a lazy list of the values [2 3 5]
   */
  static LazySeq<int> * getGenerators();
};


#endif // not defined Hamming_h
