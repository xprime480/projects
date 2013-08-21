#if ! defined(BinopGenerator_h)
#define BinopGenerator_h 1

#include <set>

#include "Form.h"
#include "SequenceGenerator.h"

namespace Sloth
{
  class BinopGenerator : public SequenceGenerator
  {
  public:
    /**
     * constructor
     *
     */
    BinopGenerator(std::string const & _op,
		   Form const & _arg1,
		   Form const & _arg2);

    static std::set<std::string> getBinopSet();

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
    Form const arg1;
    Form const arg2;

    enum { BinopArgs_Unknown, 
	   BinopArgs_SeqSeq, 
	   BinopArgs_SeqNon, 
	   BinopArgs_NonSeq, 
	   BinopArgs_NonNon 
    } type;

    Form eval(Form const & a1, Form const & a2) const;
    Form evalArith(Form const & a1, Form const & a2) const;

    Form evalCompare(Form const & a1, Form const & a2) const;

    Form evalCompareInt(Form const & a1, Form const & a2) const;
    Form evalCompareBoolean(Form const & a1, Form const & a2) const;
    Form evalCompareString(Form const & a1, Form const & a2) const;
    Form evalCompareSequence(Form const & a1, Form const & a2) const;
    Form evalCompareSymbol(Form const & a1, Form const & a2) const;
    Form evalCompareMessage(Form const & a1, Form const & a2) const;
    Form evalCompareBlob(Form const & a1, Form const & a2) const;
  };
}

#endif // not defined BinopGenerator_h
