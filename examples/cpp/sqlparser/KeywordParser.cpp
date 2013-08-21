// $Id: /home/I809989/test/cpp/sqlparser/KeywordParser.cpp#1 $
// $DateTime: Tue Nov  8 20:43:57 2011 $

#include <cstring>

#include "Token.h"

#include "KeywordParser.h"

using namespace std;
using namespace parser;

KeywordParser::KeywordParser(std::string const & _kw)
  : keyword(_kw)
{
}

Expression KeywordParser::parse(TokenStream & tokens, int flags) const
{
  TokenStream::state_type state = tokens.getState();

  tokens.forward();
  Token * t = tokens.get();
  if ( (t != NULL) && 
       (t->getType() == Token::TOKEN_SYM) && 
       (0 == strcasecmp(keyword.c_str(), t->getText().c_str())) ) {

    Expression results;
    Expression txt(t->getText().c_str());

    results.append(Expression(true));
    results.append(txt);
    results.append(txt);

    return results;
  }
  
  tokens.setState(state);
  return Expression(false);
}
