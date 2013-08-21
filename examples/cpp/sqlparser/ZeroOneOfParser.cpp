// $Id: /home/I809989/test/cpp/parser/ZeroOneOfParser.cpp#1 $
// $DateTime: Fri Apr 15 13:50:41 2011 $

#include "ZeroOneOfParser.h"

using namespace std;
using namespace parser;

ZeroOneOfParser::ZeroOneOfParser(Parser * _p)
  : parser(_p)
{
}

ParseResult ZeroOneOfParser::parse(TokenStream & tokens) const
{
  ParseResult result = parser->parse(tokens);
  if ( ! result ) {
    result = ParseResult(true);
  }

  return result;
}
