// $Id: /home/I809989/test/cpp/parser/SymbolStreamParser.h#1 $
// $DateTime: Mon Apr 18 15:04:08 2011 $

#if ! defined(SymbolStreamParser_h)
#define SymbolStreamParser_h 1

#include "Parser.h"

namespace parser {
  class SymbolStreamParser : public Parser
  {
  public:
    virtual Expression parse(TokenStream & tokens) const;
  };
}

#endif // not defined SymbolStreamParser_h
