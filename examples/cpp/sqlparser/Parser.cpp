// $Id: /home/I809989/test/cpp/parser/Parser.cpp#1 $
// $DateTime: Fri Apr 15 09:27:54 2011 $

#include "Parser.h"

using namespace std;
using namespace parser;

ParserException::ParserException(std::string const & what)
  : runtime_error(what)
{
}

ParseResult NullParser::parse(TokenStream & tokens) const
{
  return Expression(true);
}


