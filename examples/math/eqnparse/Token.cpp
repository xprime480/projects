
#include "Token.h"

Token::Token( char c, TokenType tt )
  : v( std::string( 1, c ) ) 
  , t( tt )
{
}


Token::Token( std::string const & s, TokenType tt )
  : v( s ) 
  , t( tt )
{
}

std::string const & Token::value() const
{
  return v;
}

Token::TokenType Token::type() const
{
  return t;
}


bool operator==( Token const & t1, Token const & t2 )
{
  return t1.type() == t2.type() /* && t1.value() == t2.value() */ ;
}

std::ostream & operator<<( std::ostream & os, Token const & t )
{
  os << t.value();
  return os;
}
