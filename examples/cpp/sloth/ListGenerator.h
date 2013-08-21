#if ! defined(ListGenerator_h)
#define ListGenerator_h 1

#include <vector>

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class ListGenerator : public SequenceGenerator 
  {
  public:
    /**
     * constructor
     *
     */
    ListGenerator(std::vector<Form> const & _forms);

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
    std::vector<Form> forms;
  };
}

#endif // not defined ListGenerator_h
