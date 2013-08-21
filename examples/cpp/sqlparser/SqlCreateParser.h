// $Id: /home/I809989/test/cpp/sqlparser/SqlCreateParser.h#1 $
// $DateTime: Tue Nov  8 14:31:47 2011 $

#if ! defined(SqlCreateParser_h)
#define SqlCreateParser_h 1

#include "SequenceOfParser.h"

#include "Parser.h"

namespace parser {
  class SqlCreateParser : public Parser
  {
  public:
    SqlCreateParser();

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    SequenceOfParser parser;
  };
}

#endif // not defined SqlCreateParser_h
