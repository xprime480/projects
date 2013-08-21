// $Id: /home/I809989/test/cpp/sqlparser/SqlCreateTableParser.cpp#1 $
// $DateTime: Tue Nov  8 18:51:07 2011 $

#include <vector>

#include "SqlKeywords.h"
#include "SymbolParser.h"

#include "SqlCreateTableParser.h"

using namespace std;
using namespace parser;

namespace {
  NullParser null;
  SymbolParser symbol;
}

SqlCreateTableParser::SqlCreateTableParser()
{
  parser.append(&kwTable);
  parser.append(&null);
  parser.append(&symbol);
}

Expression SqlCreateTableParser::parse(TokenStream & tokens, int flags) const
{
  return parser.parse(tokens, flags);
}
