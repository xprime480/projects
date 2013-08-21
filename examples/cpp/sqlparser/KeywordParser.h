// $Id: /home/I809989/test/cpp/sqlparser/KeywordParser.h#1 $
// $DateTime: Tue Nov  8 20:42:33 2011 $

#if ! defined(KeywordParser_h)
#define KeywordParser_h 1

#include "Parser.h"

namespace parser {
  class KeywordParser : public Parser
  {
  public:
    KeywordParser(std::string const & _kw);

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    std::string keyword;
  };
}

#endif // not defined KeywordParser_h
