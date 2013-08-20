// $Id: /home/I809989/test/cpp/parser/AnyOfParser.h#1 $
// $DateTime: Fri Apr 15 10:50:55 2011 $

#if ! defined(AnyOfParser_h)
#define AnyOfParser_h 1

#include <vector>

#include "Parser.h"

namespace parser {

  class AnyOfParser : public Parser
  {
  public:
    AnyOfParser(std::vector<Parser *> const & _ps);

    virtual Expression parse(TokenStream & tokens) const;

  private:

    std::vector<Parser *> parsers;
  };

}

#endif // not defined AnyOfParser_h
