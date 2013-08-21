#if ! defined(Infinite_h)
#define Infinite_h 1

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class Infinite : public SequenceGenerator
  {
  public:
    Infinite(Form const & _v);

    virtual bool isNil() const;
    virtual Form head() const;
    virtual Form tail() const;

    virtual std::string toString() const;

  private:
    Form value;
  };
}



#endif // not defined Infinite_h
