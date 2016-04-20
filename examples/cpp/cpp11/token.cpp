
#include "token.h"

using std::string;

Token::Token(string & _v)
  : value(_v)
{
}
  
string Token::format() const
{
  return value;
}
