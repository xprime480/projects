// $Id: /home/I809989/test/cpp/parser/AnyOfParser.cpp#1 $
// $DateTime: Fri Apr 15 12:31:41 2011 $

#include "AnyOfParser.h"

using namespace std;
using namespace parser;

AnyOfParser::AnyOfParser(vector<Parser *> const & _ps)
  : parsers(_ps)
{
}

Expression AnyOfParser::parse(TokenStream & tokens) const
{
  typedef vector<Parser *>::const_iterator iter;
  for ( iter i = parsers.begin() ; i != parsers.end() ; ++i ) {
    Expression result = (*i)->parse(tokens);
    if ( result ) {
      return result;
    }
  }

  return Expression(false);
}
