// $Id: /home/I809989/test/cpp/parser/SymbolStreamParser.cpp#1 $
// $DateTime: Mon Apr 18 15:04:48 2011 $

#include "Token.h"

#include "SymbolStreamParser.h"

using namespace std;
using namespace parser;
ParseResult SymbolStreamParser::parse(TokenStream & tokens) const
{
  TokenStream::state_type original = tokens.getState();
  ParseResult final(false);

  while ( true ) {
    TokenStream::state_type state = tokens.getState();

    tokens.forward();
    Token * t = tokens.get();

    if ( ! t ) {
      tokens.setState(state);
      break;
    }

    if ( t->getType() == Token::TOKEN_SYM ) {
      final.success = true;
      final.match += t->getText();
      final.parts.push_back(t->getText());
    }
    else if ( t->getType() == Token::TOKEN_EOL ) {
      final.success = true;
      final.match += t->getText();
    }
    else {
      tokens.setState(state);
      break;
    }
  }

  if ( ! final.success ) {
    tokens.setState(original);
  }

  return final;
}
