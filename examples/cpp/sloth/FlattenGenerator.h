#if ! defined(FlattenGenerator_h)
#define FlattenGenerator_h 1

#include <vector>

#include "SequenceGenerator.h"

namespace Sloth
{
  class FlattenGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    FlattenGenerator(Form const & _form);

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
    mutable bool evaled;
    mutable Form flattened;

    void helper(Form const & f, std::vector<Form> & forms) const;
  };
}

#endif // not defined FlattenGenerator_h
