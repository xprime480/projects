#if ! defined(TakeIfGenerator_h)
#define TakeIfGenerator_h 1

#include "SequenceGenerator.h"

namespace Sloth
{
  class TakeIfGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    TakeIfGenerator(Form const & _form, Form const & _pred);

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
    std::pair<Form const, Form const> args; // <form, pred>
    std::pair<Form, Form> advance(Form form, Form pred);
  };
}

#endif // not defined TakeIfGenerator_h
