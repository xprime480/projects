#if ! defined(GeneralizedFibonacciGenerator_h)
#define GeneralizedFibonacciGenerator_h 1

#include "SequenceGenerator.h"

namespace Sloth
{
  class GeneralizedFibonacciGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     */
    GeneralizedFibonacciGenerator(int _a, int _b);

    /**
     * isNil()
     *
     * See base class for documentation.
     */ 
    virtual bool isNil() const;

    /**
     * head
     *
     * See base class for documentation.
     */ 
    virtual Form head() const;

    /**
     * tail
     *
     * See base class for documentation.
     */ 
    virtual Form tail() const;

    virtual std::string toString() const;

  private:
    int const a;
    int const b;
  };
}

#endif // not defined GeneralizedFibonacciGenerator_h
