#if ! defined(SequenceGenerator_h)
#define SequenceGenerator_h 1

#include <string>

namespace Sloth
{
  class Form;

  class SequenceGenerator
  {
  public:
    virtual ~SequenceGenerator() 
    {
    }

    virtual bool isNil() const = 0;
    virtual Form head() const = 0;
    virtual Form tail() const = 0;

    virtual std::string toString() const = 0;

  protected:
    Form headFromNil() const;
  };
}

#endif // not defined SequenceGenerator_h
