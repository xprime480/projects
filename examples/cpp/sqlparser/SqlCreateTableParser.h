// $Id: /home/I809989/test/cpp/sqlparser/SqlCreateTableParser.h#1 $
// $DateTime: Tue Nov  8 18:50:29 2011 $

#if ! defined(SqlCreateTableParser_h)
#define SqlCreateTableParser_h 1

#include "Parser.h"
#include "SequenceOfParser.h"

namespace parser {
  class SqlCreateTableParser : public Parser
  {
  public:
    SqlCreateTableParser();

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    SequenceOfParser parser;
  };
}


#endif // not defined SqlCreateTableParser_h
