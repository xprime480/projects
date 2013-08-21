#if ! defined(TakeGenerator_h)
#define TakeGenerator_h 1

#include "SequenceGenerator.h"

namespace Sloth
{
  class TakeGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    TakeGenerator(Form const & _form, int _count);

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
    int        count;
  };
}

#endif // not defined TakeGenerator_h
