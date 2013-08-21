// $Id: /home/I809989/test/cpp/parser/AnyCharOfParser.cpp#1 $
// $DateTime: Fri Apr 15 10:54:51 2011 $

#include "Token.h"

#include "AnyCharOfParser.h"

using namespace std;
using namespace parser;

AnyCharOfParser::AnyCharOfParser(std::string const & _cs)
  : charset(_cs)
{
}

Expression AnyCharOfParser::parse(TokenStream & tokens, int flags) const
{
  TokenStream::state_type state = tokens.getState();

  tokens.forward();
  Token * t = tokens.get();
  if ( (t != NULL) && 
       (t->getType() == Token::TOKEN_TEXT) && 
       (t->getText().size() == 1) &&
       (string::npos != charset.find(t->getText().at(0))) ) {

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

string const parser::lowercase("abcdefghijklmnopqrstuvwxyz");
string const parser::uppercase("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
string const parser::digits("0123456789");
string const parser::hexdigits("abcdefABCDEF0123456789");
string const parser::whitespace(" 	");


