// $Id: /home/I809989/test/cpp/sqlparser/SymbolParser.h#1 $
// $DateTime: Wed Nov  9 11:46:48 2011 $

#if ! defined(SymbolParser_h)
#define SymbolParser_h 1

#include "Parser.h"

namespace parser {
  class SymbolParser : public Parser
  {
  public:
    SymbolParser();

    virtual Expression parse(TokenStream & tokens, int flags) const;
  };
}

#endif // not defined SymbolParser_h
