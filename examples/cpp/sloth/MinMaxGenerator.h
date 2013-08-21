#if ! defined(MinMaxGenerator_h)
#define MinMaxGenerator_h 1

#include "SequenceGenerator.h"

namespace Sloth
{
  class MinMaxGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    MinMaxGenerator(Form const & _form);

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
    Form const form;
    mutable int  min;
    mutable int  max;
    mutable bool empty;
    mutable int  evaled;
  };
}

#endif // not defined MinMaxGenerator_h
