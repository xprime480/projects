// $Id: /home/I809989/test/cpp/parser/CharTokenStream.cpp#1 $
// $DateTime: Mon Apr 18 13:21:42 2011 $

#include <string>

#include "Token.h"

#include "CharTokenStream.h"

using namespace std;
using namespace parser;

CharTokenStream::CharTokenStream(CharacterStream & chars)
  : TokenStream(chars)
{
}

Token * CharTokenStream::getNextToken()
{
  string buf;
  char c = skipws();
  if ( c == -1 ) {
    return 0;
  }

  buf += c;
  return new Token(Token::TOKEN_TEXT, buf);
}
