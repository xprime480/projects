// $Id: /home/I809989/test/cpp/sqlparser/SqlParser.cpp#1 $
// $DateTime: Tue Nov  8 13:52:38 2011 $

#include <vector>

#include "SqlCreateTableParser.h"
#include "SequenceOfParser.h"
#include "SqlKeywords.h"

#include "SqlCreateParser.h"

using namespace std;
using namespace parser;

namespace {
  SqlCreateTableParser createTableParser;
}

SqlCreateParser::SqlCreateParser()
{
  parser.append(&kwCreate);
  parser.append(&createTableParser);
}

Expression SqlCreateParser::parse(TokenStream & tokens, int flags) const
{
  return parser.parse(tokens, flags);
}
