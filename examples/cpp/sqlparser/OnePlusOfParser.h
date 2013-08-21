// $Id: /home/I809989/test/cpp/parser/OnePlusOfParser.h#1 $
// $DateTime: Fri Apr 15 14:01:04 2011 $

#if ! defined(OnePlusOfParser_h)
#define OnePlusOfParser_h 1

#include "Parser.h"

namespace parser {

  class OnePlusOfParser : public Parser
  {
  public:
    OnePlusOfParser(Parser * _p);

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    Parser * parser;
  };
}

#endif // not defined OnePlusOfParser_h
