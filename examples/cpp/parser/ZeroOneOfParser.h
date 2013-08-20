// $Id: /home/I809989/test/cpp/parser/ZeroOneOfParser.h#1 $
// $DateTime: Fri Apr 15 13:48:50 2011 $

#if ! defined(ZeroOneOfParser_h)
#define ZeroOneOfParser_h 1

#include "Parser.h"

namespace parser {

  class ZeroOneOfParser : public Parser
  {
  public:
    ZeroOneOfParser(Parser * _p);

    virtual Expression parse(TokenStream & tokens) const;

  private:
    Parser * parser;
  };
}

#endif // not defined ZeroOneOfParser_h
