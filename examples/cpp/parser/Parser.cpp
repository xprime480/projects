// $Id: /home/I809989/test/cpp/parser/Parser.cpp#1 $
// $DateTime: Fri Apr 15 09:27:54 2011 $

#include "Parser.h"

using namespace std;
using namespace parser;

ParserException::ParserException(std::string const & what)
  : runtime_error(what)
{
}

Expression NullParser::parse(TokenStream & tokens) const
{
  Expression result;
  result.append(Expression(true));
  result.append(Expression(""));
  result.append(nil);
  return result;
}


