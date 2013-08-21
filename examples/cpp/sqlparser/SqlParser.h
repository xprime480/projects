// $Id: /home/I809989/test/cpp/sqlparser/SqlParser.h#1 $
// $DateTime: Tue Nov  8 13:51:44 2011 $

#if ! defined(SqlParser_h)
#define SqlParser_h 1

#include "Parser.h"
#include "AnyOfParser.h"

namespace parser {
  class SqlParser : public Parser
  {
  public:
    SqlParser();

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    AnyOfParser parser;
  };
}

#endif // not defined SqlParser_h
