// $Id: /home/I809989/test/cpp/parser/ZeroOneOfParser.cpp#1 $
// $DateTime: Fri Apr 15 13:50:41 2011 $

#include "ZeroOneOfParser.h"

using namespace std;
using namespace parser;

ZeroOneOfParser::ZeroOneOfParser(Parser * _p)
  : parser(_p)
{
}

Expression ZeroOneOfParser::parse(TokenStream & tokens, int flags) const
{
  Expression result = parser->parse(tokens, flags);
  if ( ! result ) {
    result = Expression();
    result.append(Expression(true));
    result.append(Expression());
    result.append(Expression(""));
  }

  return result;
}
