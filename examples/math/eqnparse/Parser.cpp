
#include <map>
#include <iostream>

#include "Equation.h"
#include "Parser.h"
#include "Token.h"

Token const T_EOF( "", Token::TT_EOF );

Token const T_LPAREN( "(", Token::TT_LPAREN );
Token const T_RPAREN( ")", Token::TT_RPAREN );
Token const T_EQ    ( "=", Token::TT_EQ );
Token const T_PLUS  ( "+", Token::TT_PLUS );
Token const T_MINUS ( "-", Token::TT_MINUS );
Token const T_TIMES ( "*", Token::TT_TIMES );
Token const T_DIVS  ( "/", Token::TT_DIVS );
Token const T_POWER ( "^", Token::TT_POWER );
Token const T_COMMA ( ",", Token::TT_COMMA );

Token const T_EXP( "EXP", Token::TT_KWD );
Token const T_VAR( "any", Token::TT_VAR );

Parser::Parser( std::istream & s )
  : input( s )
{
}


Equation * Parser::parse()
{
  next_token = 0;
  parse_prelude();
  Equation * eqn = parse_eqn();
  assert_eof();
  return eqn;
}

bool Parser::accept( Token const & t )
{
  Token const & p = peek();
  if ( t != p ) {
    std::cerr << "expected " << t << ", got " << p << "\n";
    return false;
  }
  ++next_token;
  return true;
}

void Parser::parse_prelude()
{
  static Token const F( "f", Token::TT_VAR );
  if ( ! accept( F ) ) {
    throw "error parsing prelude";
  }
  if ( ! accept( T_LPAREN ) ) {
    throw "error parsing prelude";
  }
  parse_varlist();
  if ( ! accept( T_RPAREN ) ) {
    throw "error parsing prelude";
  }
  if ( ! accept( T_EQ ) ) {
    throw "error parsing prelude";
  }
}

void Parser::parse_varlist()
{
  size_t pos = 0;

  while ( true ) {
    Token const & p = peek();
    if ( p != T_VAR ) {
      if ( 0 != pos ) {
	throw "malformed variable list in prelude";
      }
      return;
    }

    char var = p.value()[0];
    if ( 0 != symbols[ var ] ) {
      throw "duplicate variable in prelude";
    }
    symbols[ var ] = pos++;
    accept( T_VAR );

    if ( T_COMMA != peek() ) {
      break;
    }
    accept( T_COMMA );
    
  }
}

Equation * Parser::parse_eqn()
{
  return 0;
}

void Parser::assert_eof()
{
  if ( ! accept( T_EOF ) ) {
    throw "Extra Input found at end";
  }
}

Token const & Parser::peek()
{
  while ( token_stream.size() <= next_token ) {
    // lex a token into the stream
    if ( ! lex() ) {
      next_token = token_stream.size() - 1;
    }
  }
  
  return token_stream.at( next_token );
}

bool Parser::lex()
{
  static std::string buffer;

  if ( ! token_stream.empty() && T_EOF == token_stream.back() ) {
    return false;		// already past eof
  }

  while ( true ) {
    fill_buffer( buffer );
    if ( buffer.empty() ) {
      token_stream.push_back( T_EOF );
      return true;
    }

    if ( buffer.size() >= 3 ) {
      if ( buffer.substr( 0, 3 ) == "exp" ) {
	token_stream.push_back( T_EXP );
	buffer = buffer.substr( 3 );
	return true;
      }
    }

    char c = buffer[ 0 ];
    if ( std::isdigit( c ) || '.' == c ) {
      lex_number( buffer );
      return true;
    }

    while ( ! buffer.empty() ) {
      buffer = buffer.substr( 1 );

      if ( std::isalpha( c ) ) {
	Token t( c, Token::TT_VAR );
	token_stream.push_back( t );
	return true;
      }
  
      if ( std::isprint( c ) ) {
	Token::TokenType ty;
	switch ( c ) {
	  case '(':
	    ty = Token::TT_LPAREN;
	    break;
	  case ')':
	    ty = Token::TT_RPAREN;
	    break;
	  case '=':
	    ty = Token::TT_EQ;
	    break;
	  case '+':
	    ty = Token::TT_PLUS;
	    break;
	  case '-':
	    ty = Token::TT_MINUS;
	    break;
	  case '*':
	    ty = Token::TT_TIMES;
	    break;
	  case '/':
	    ty = Token::TT_DIVS;
	    break;
	  case '^':
	    ty = Token::TT_POWER;
	    break;
	  case ',':
	    ty = Token::TT_COMMA;
	    break;
	  default:
	    ty = Token::TT_VAR;
	    break;
	}

	Token t( c, ty );
	token_stream.push_back( t );
	return true;
      }
    }
  }

  return false;
}

void Parser::fill_buffer( std::string & buffer )
{
  std::string::size_type pos;

  pos = buffer.find_first_not_of( " \t\n" );
  if ( std::string::npos == pos ) {
    buffer = "";
  }
  else {
    buffer = buffer.substr( pos );
    return;
  }

  bool inword( false );
  while ( true ) {
    int c = input.get();
    if ( input.eof() ) {
      return;
    }
    if ( std::isspace( c ) ) {
      if ( inword ) {
	buffer += ' ';
	return;
      }
      continue;
    }
    inword = true;
    buffer += (char) std::tolower( c );
  }
}

std::string grab_digits( std::string & buffer ) 
{
  std::string::size_type pos;
  std::string digits;

  pos = buffer.find_first_not_of( "0123456789" );
  digits = buffer.substr( 0, pos );
  buffer = buffer.substr( pos );

  return digits;
}

void Parser::lex_number( std::string & buffer )
{
  std::string num;
  
  num += grab_digits( buffer );

  if ( ! buffer.empty() && '.' == buffer[0] ) {
    num += '.';
    buffer = buffer.substr( 1 );

    num += grab_digits( buffer );
  }

  Token t( num, ( num == "." ) ? Token::TT_VAR : Token::TT_NUM );
  token_stream.push_back( t );
}

