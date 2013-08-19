#if ! defined(Fibonacci_h)
#define Fibonacci_h 1

#include "GeneralizedFibonacci.h"

/**
 * Fibonacci
 *
 * This class generates the fibonacci sequence (on integers).
 * 
 * Examples:
 *  -> (1 1 2 3 5 8 ...)
 *
 */
class Fibonacci : public GeneralizedFibonacci<int>
{
public:
  /**
   * constructor
   */
  Fibonacci();
};


#endif // not defined Fibonacci_h
