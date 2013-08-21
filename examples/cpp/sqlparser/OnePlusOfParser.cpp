// $Id: /home/I809989/test/cpp/parser/OnePlusOfParser.cpp#1 $
// $DateTime: Fri Apr 15 14:14:43 2011 $

#include <cstring>
#include <iostream>

#include "OnePlusOfParser.h"

using namespace std;
using namespace parser;

OnePlusOfParser::OnePlusOfParser(Parser * _p)
  : parser(_p)
{
}

Expression OnePlusOfParser::parse(TokenStream & tokens, int flags) const
{
  TokenStream::state_type state = tokens.getState();

  Expression final;
  final.append(Expression(true));
  final.append(Expression());
  final.append(Expression(""));

  Expression result = parser->parse(tokens, flags);

  while ( result ) {
    size_t len = strlen(result.nth(2));
    if ( len == 0 ) {
      tokens.setState(state);
      throw ParserException("OnePlusOfParser: zero length part");
    }
    
    final.nth(1).append(result.nth(1));
    final.nth(2).addText(result.nth(2));

    TokenStream::state_type lastGood = tokens.getState();
    result = parser->parse(tokens, flags);
    if ( ! result ) {
      tokens.setState(lastGood);
    }
  }

  if ( ! final.nth(1) ) {
    tokens.setState(state);
    return Expression(false);
  }

  return final;
}
