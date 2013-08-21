#if ! defined(UnopGenerator_h)
#define UnopGenerator_h 1

#include <set>

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class UnopGenerator : public SequenceGenerator
  {
  public:
    /**
     * constructor
     *
     */
    UnopGenerator(std::string const & _op, Form const & _arg);

    static std::set<std::string> getUnopSet();

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
    std::string const op;
    Form const arg;

    enum { UnopArgs_Unknown, 
	   UnopArgs_Seq, 
	   UnopArgs_Non
    } type;

    Form eval(Form const & a) const;
  };
}

#endif // not defined UnopGenerator_h
