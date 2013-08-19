#include "TokenStream.h"

using namespace std;
using namespace lazy;

TokenStream::TokenStream()
  : LazySeq<Token>()
{
}

TokenStream::TokenStream(string const & input)
  : LazySeq<Token>()
  , rest(input)
{
  skipWS();
  if ( rest.empty() ) {
    return;
  }

  this->empty = false;
  size_t skip = 0;
  if ( rest[0] == '(' ) {
    this->head.type = Token::TT_LPAREN;
    this->head.contents = "(";
    skip = 1;
  }
  else if ( rest[0] == ')' ) {
    this->head.type = Token::TT_RPAREN;
    this->head.contents = ")";
    skip = 1;
  }
  else if ( rest[0] == '[' ) {
    this->head.type = Token::TT_LSQUARE;
    this->head.contents = "[";
    skip = 1;
  }
  else if ( rest[0] == ']' ) {
    this->head.type = Token::TT_RSQUARE;
    this->head.contents = "]";
    skip = 1;
  }
  else if ( rest[0] == '_' ) {
    this->head.type = Token::TT_PLACEHOLDER;
    this->head.contents = "_";
    skip = 1;
  }
  else if ( (skip = getUnaryOperator()) > 0 ) {
    this->head.type = Token::TT_UNARY_OPERATOR;
    this->head.contents = rest.substr(0, skip);
  }
  else if ( (skip = getBinaryOperator()) > 0 ) {
    this->head.type = Token::TT_BINARY_OPERATOR;
    this->head.contents = rest.substr(0, skip);
  }
  else if ( (skip = getKeyword()) > 0 ) {
    this->head.type = Token::TT_KEYWORD;
    this->head.contents = rest.substr(0, skip);
  }
  else if ( (skip = getInteger()) > 0 ) {
    this->head.type = Token::TT_INTEGER;
    this->head.contents = rest.substr(0, skip);
  }
  else {
    this->head.type = Token::TT_UNKNOWN;
    this->head.contents = rest;
    skip = rest.size();
  }

  rest = rest.substr(skip);
}

TokenStream::~TokenStream()
{
}

TokenStream * TokenStream::tail()
{
  return new TokenStream(rest);
}

void TokenStream::skipWS()
{
  char const * data = rest.c_str();
  while ( *data ) {
    if ( *data == '#' ) {
      while ( *data ) {
	if ( *data == '\n' ) {
	  break;
	}
	++data;
      }
      continue;
    }
    if ( ! isspace(*data) ) {
      break;
    }
    ++data;
  }

  rest = data;
}

size_t TokenStream::getUnaryOperator()
{
  return 0;
}

size_t TokenStream::getBinaryOperator()
{
  skipWS();
  if ( rest.empty() ) {
    return 0;
  }

  if ( rest[0] == '*' || rest[0] == '<' ) {
    return 1;
  }

  return 0;
}

size_t TokenStream::getKeyword()
{
  skipWS();
  if ( rest.empty() || ! isalpha(rest[0]) ) {
    return 0;
  }

  char const * data = rest.c_str();
  ++data;
  while ( *data ) {
    if ( ! isalnum(*data) ) {
      break;
    }
    ++data;
  }
  
  size_t len = data - rest.c_str();
  return len;
}

size_t TokenStream::getInteger()
{
  skipWS();
  if ( rest.empty() ) {
    return 0;
  }

  bool sign = false;
  char const * data = rest.c_str();
  if ( *data == '-' || *data == '+' ) {
    ++data;
    sign = true;
  }
  while ( *data ) {
    if ( ! isdigit(*data) ) {
      break;
    }
    ++data;
  }

  size_t len = data - rest.c_str();
  if ( len == 1 && sign ) {
    len = 0;
  }
  return len;
}
