// $Id: /home/I809989/test/cpp/sqlparser/SymbolParser.cpp#1 $
// $DateTime: Wed Nov  9 11:47:45 2011 $

#include "Token.h"

#include "SymbolParser.h"

using namespace std;
using namespace parser;

SymbolParser::SymbolParser()
{
}

Expression SymbolParser::parse(TokenStream & tokens, int flags) const
{
  TokenStream::state_type state = tokens.getState();

  tokens.forward();
  Token * t = tokens.get();
  if ( (t != NULL) && 
       (t->getType() == Token::TOKEN_SYM) ) {

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
