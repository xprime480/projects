#if ! defined(CountGenerator_h)
#define CountGenerator_h 1

#include "Form.h"
#include "IntegerGenerator.h"

namespace Sloth
{
  class CountGenerator : public IntegerGenerator
  {
  public:
    CountGenerator(Form const & _form);

    virtual int value() const;

    virtual std::string toString() const;

  private:
    Form form;
    mutable int  count;
    mutable bool evaled;
  };

}

#endif // not defined CountGenerator_h
