#if ! defined(FormFactory_h)
#define FormFactory_h 1

#include <set>
#include <string>
#include <vector>

#include "Form.h"
#include "IntegerGenerator.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class Form;

  class FormFactory
  {
  public:
    static void incref(Form const * form);
    static void decref(Form const * form);

    static Form makeNil();
    static Form makeMessage(std::string const & message);
    static Form makeInt(int value);
    static Form makeInt(IntegerGenerator * generator);
    static Form makeString(std::string const & value);
    static Form makeBlob(void * _value, void(*_handler)(void*));
    static Form makeSequence(SequenceGenerator * generator);
    static Form makeSymbol(std::string const & name);
    static Form makeBoolean(bool value);
  };
}

#endif // not defined FormFactory_h
