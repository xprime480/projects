// $Id: /home/I809989/test/cpp/parser/SequenceOfParser.h#1 $
// $DateTime: Fri Apr 15 13:08:47 2011 $

#if ! defined(SequenceOfParser_h)
#define SequenceOfParser_h 1

#include <vector>

#include "Parser.h"

namespace parser {

  class SequenceOfParser : public Parser
  {
  public:
    SequenceOfParser(std::vector<Parser *> const & _ps);

    virtual Expression parse(TokenStream & tokens) const;

  private:
    std::vector<Parser *> parsers;
  };

}

#endif // not defined SequenceOfParser_h
