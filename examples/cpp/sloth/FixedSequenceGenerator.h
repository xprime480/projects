#if ! defined(FixedSequenceGenerator_h)
#define FixedSequenceGenerator_h 1

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class FixedSequenceGenerator : public SequenceGenerator
  {
  public:
    FixedSequenceGenerator(Form const & _b, size_t _p = 0);

    virtual bool isNil() const;
    virtual Form head() const;
    virtual Form tail() const;

    virtual std::string toString() const;

  private:
    Form blob;
    size_t pos;
  };
}

#endif // not defined FixedSequenceGenerator_h
