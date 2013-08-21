#if ! defined(NilForm_h)
#define NilForm_h 1

#include "FormImpl.h"

namespace Sloth {

  struct NilFormTag {};

  template <>
  class FormImpl<NilFormTag> : public Form {
  public :
    virtual bool isNil()
    {
      return true;
    }
  protected:
  private:
  };

}

#endif
