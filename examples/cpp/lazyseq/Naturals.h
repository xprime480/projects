#if ! defined(Naturals_h)
#define Naturals_h 1

#include <limits>

#include "Slice.h"

using namespace std;

/**
 * Naturals
 *
 * This class lazily builds a sequence of the natural numbers, up to
 * the maximum value representable by the type
 * 
 * Examples:
 *   -> (1 2 3 4 ...)
 */
template <typename T = int>
class Naturals : public Slice<T>
{
public:
  /**
   * constructor
   */
  Naturals()
    : Slice<T>(1, numeric_limits<T>::max(), 1)
  {
  }

};


#endif // not defined Naturals_h
