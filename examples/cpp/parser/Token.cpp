// $Id: /home/I809989/test/cpp/parser/Token.cpp#1 $
// $DateTime: Mon Apr 18 12:19:45 2011 $

#include "Token.h"

using namespace std;
using namespace parser;

Token::Token(types _typ, std::string const & _txt)
  : type(_typ)
  , text(_txt)
{
}

Token::types Token::getType() const
{
  return type;
}

std::string const & Token::getText() const
{
  return text;
}
