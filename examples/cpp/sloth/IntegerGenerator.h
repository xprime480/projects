#if ! defined(IntegerGenerator_h)
#define IntegerGenerator_h 1

#include <string>

namespace Sloth
{
  class Form;

  class IntegerGenerator
  {
  public:
    virtual ~IntegerGenerator() 
    {
    }

    virtual int value() const = 0;

    virtual std::string toString() const = 0;
  };
}

#endif // not defined IntegerGenerator_h
