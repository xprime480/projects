#if ! defined(DropGenerator_h)
#define DropGenerator_h 1

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class DropGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    DropGenerator(Form const & _form, int _count);

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
    mutable Form form;
    mutable int  count;
    mutable bool evaled;

    void eval() const;
  };
}

#endif // not defined DropGenerator_h
