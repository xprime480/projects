#if ! defined(Appender_h)
#define Appender_h 1

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class Form;

  class Appender : public SequenceGenerator
  {
  public:
    /**
     * constructor
     *
     */
    Appender(Form const & _f1, Form const & _f2);

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
    Form f1;
    Form f2;
  };
}


#endif // not defined Appender_h
