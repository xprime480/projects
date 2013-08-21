// $Id: /home/I809989/test/cpp/parser/SingleCharParser.cpp#1 $
// $DateTime: Fri Apr 15 10:35:49 2011 $

#include "Token.h"

#include "SingleCharParser.h"

using namespace std;
using namespace parser;

SingleCharParser::SingleCharParser(char _c)
{
  c += _c;
}

ParseResult SingleCharParser::parse(TokenStream & tokens) const
{
  TokenStream::state_type state = tokens.getState();

  tokens.forward();
  Token * t = tokens.get();
  if ( (t != NULL) && 
       (t->getType() == Token::TOKEN_TEXT) && 
       (t->getText() == c) ) {
    ParseResult res;
    ParseResult txt(t->getText().c_str());
    res.append(txt);
    return res;
  }
  
  tokens.setState(state);
  return ParseResult(false);
}
