// $Id: /home/I809989/test/cpp/parser/SymbolStreamParser.cpp#1 $
// $DateTime: Mon Apr 18 15:04:48 2011 $

#include "Token.h"

#include "SymbolStreamParser.h"

using namespace std;
using namespace parser;
Expression SymbolStreamParser::parse(TokenStream & tokens, int flags) const
{
  TokenStream::state_type original = tokens.getState();
  Expression final;
  final.append(Expression(true));
  final.append(Expression());
  final.append(Expression(""));

  while ( true ) {
    TokenStream::state_type state = tokens.getState();

    tokens.forward();
    Token * t = tokens.get();

    if ( ! t ) {
      tokens.setState(state);
      break;
    }

    if ( t->getType() == Token::TOKEN_SYM ) {
      Expression txt(t->getText().c_str());
      final.nth(1).append(txt);
      Expression & e = final.nth(2);
      if ( e.size() > 0 ) {
	e.addText(" ");
      }
      e.addText(txt);
    }
    else if ( t->getType() == Token::TOKEN_EOL ) {
      // do nothing
    }
    else {
      tokens.setState(state);
      break;
    }
  }

  if ( ! final ) {
    tokens.setState(original);
  }

  return final;
}
