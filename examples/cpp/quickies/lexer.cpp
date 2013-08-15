#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>

struct Token
{
  enum TokenType {
    TT_STRING,
    TT_SYMBOL,
    TT_INTEGER,
    TT_FLOAT,
    TT_OPERATOR,
  };

  TokenType type;
  std::string text;
};

std::ostream & operator<<( std::ostream & os, Token const & t )
{
  std::stringstream s;
  s << '{';
  switch ( t.type ) {
  case Token::TT_STRING:
    s << "TT_STRING";
    break;
  case Token::TT_SYMBOL:
    s << "TT_SYMBOL";
    break;
  case Token::TT_INTEGER:
    s << "TT_INTEGER";
    break;
  case Token::TT_FLOAT:
    s << "TT_FLOAT";
    break;
  case Token::TT_OPERATOR:
    s << "TT_OPERATOR";
    break;
  default:
    s << "?";
  }
  s << ": " << t.text << "}";
  os << s.str();
  return os;
}

std::string next_line( std::istream & is ) 
{
  std::string s;

  while ( is ) {
    int c = is.get();
    if ( EOF == c || '\n' == (char) c ) {
      break;
    }
    s += (char) c;
  }

  return s;
}

void lex_string( char const *& pch, Token & token, char end )
{
  bool quoted( false );
  while ( *pch ) {
    if ( quoted ) {
      token.text += *pch;
      quoted = false;
    }
    else if ( '\\' == *pch ) {
      quoted = true;
    }
    else if ( end == *pch ) {
      ++pch;
      break;
    }
    else {
      token.text += *pch;
    }
    ++pch;
  }
}

void lex_symbol( char const *& pch, Token & token )
{
  while ( *pch && std::isalnum( *pch ) || '_' == *pch ) {
    token.text += *pch;
    ++pch;
  }
}

bool lex_numeric( char const *& pch, Token & token )
{
  if ( ! std::isdigit( *pch ) && '.' != *pch ) {
    return false;
  }

  bool point_seen( false );

  while ( *pch && ( std::isdigit( *pch ) || '.' == *pch ) ) {
    if ( std::isdigit( *pch ) ) {
      token.text += *pch;
      ++pch;
    }
    else if ( '.' == *pch ) {
      if ( point_seen ) {
	// only one decimal place
	break;
      }
      else {
	point_seen = true;
	token.text += *pch;
	++pch;
      }
    }
    else {
      break;
    }
  }

  token.type = point_seen ? Token::TT_FLOAT : Token::TT_INTEGER;
  return true;
}

bool next_token( std::string & input, Token & token ) 
{
  char const * pch = input.c_str();
  while ( *pch && std::isspace( *pch ) ) {
    ++pch;
  }
  if ( ! *pch || '#' == *pch ) {
    input = std::string( "" );
    return false;
  }

  if ( '"' == *pch || '\'' == *pch ) {
    token.type = Token::TT_STRING;
    char delim = *pch;
    ++pch;
    lex_string( pch, token, delim );
  }
  else if ( '_' == *pch || std::isalpha( *pch ) ) {
    token.type = Token::TT_SYMBOL;
    lex_symbol( pch, token );
  }
  else if ( ! lex_numeric( pch, token ) ) {
    token.type = Token::TT_OPERATOR;
    token.text = std::string( 1, *pch );
    ++pch;
  }

  input = std::string( pch );
  return true;
}

void lex( std::istream & is )
{
  while ( is ) {
    std::string line = next_line( is );
    Token token;
    while ( next_token( line, token ) ) {
      std::cout << token << "\n";
      token.text = std::string( "" );
    }
  }
}

int main( int argc, char ** argv ) 
{
  if ( 1 == argc ) {
    lex( std::cin );
  }
  else {
    for ( size_t i = 1 ; i < argc ; ++i ) {
      std::ifstream f( argv[i] );
      lex( f );
    }
  }
  return 0;
}
