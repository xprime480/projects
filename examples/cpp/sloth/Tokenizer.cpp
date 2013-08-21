
#include "Tokenizer.h"

using namespace std;
using namespace Sloth;

Tokenizer::Tokenizer()
{
}

void Tokenizer::tokenize(string const & input)
{
  if ( ! rest.empty() ) {
    rest += " ";
  }
  rest += input;
}

bool Tokenizer::empty() const
{
  if ( tokens.empty() ) {
    lex();
  }
  return tokens.empty();
}

Token Tokenizer::front() const
{
  Token t;
  if ( ! empty() ) {
    t = tokens.front();
  }
  return t;
}

void Tokenizer::next()
{
  if ( ! empty() ) {
    tokens.pop_front();
  }
}

void Tokenizer::lex() const
{
  skipWS();
  if ( rest.empty() ) {
    return;
  }

  size_t skip = 0;
  Token t;
  if ( rest[0] == '(' ) {
    t.type = Token::TT_LPAREN;
    t.contents = "(";
    skip = 1;
  }
  else if ( rest[0] == ')' ) {
    t.type = Token::TT_RPAREN;
    t.contents = ")";
    skip = 1;
  }
  else if ( rest[0] == '[' ) {
    t.type = Token::TT_LSQUARE;
    t.contents = "[";
    skip = 1;
  }
  else if ( rest[0] == ']' ) {
    t.type = Token::TT_RSQUARE;
    t.contents = "]";
    skip = 1;
  }
  else if ( rest[0] == '{' ) {
    t.type = Token::TT_LCURLY;
    t.contents = "{";
    skip = 1;
  }
  else if ( rest[0] == '}' ) {
    t.type = Token::TT_RCURLY;
    t.contents = "}";
    skip = 1;
  }
  else if ( rest[0] == '_' ) {
    t.type = Token::TT_PLACEHOLDER;
    t.contents = "_";
    skip = 1;
  }
  else if ( (skip = getString()) > 0 ) {
    t.type = Token::TT_STRING;
    t.contents = rest.substr(1, skip-2); // lose the quotation marks
  }
  else if ( (skip = getSymbol()) > 0 ) {
    t.type = Token::TT_SYMBOL;
    t.contents = rest.substr(0, skip);
  }
  else if ( (skip = getBoolean()) > 0 ) {
    t.type = Token::TT_BOOLEAN;
    t.contents = rest.substr(0, skip);
  }
  else if ( (skip = getKeyword()) > 0 ) {
    t.type = Token::TT_KEYWORD;
    t.contents = rest.substr(0, skip);
  }
  else if ( (skip = getInteger()) > 0 ) {
    t.type = Token::TT_INTEGER;
    t.contents = rest.substr(0, skip);
  }
  else if ( (skip = getOperator()) > 0 ) {
    t.type = Token::TT_OPERATOR;
    t.contents = rest.substr(0, skip);
  }
  else {
    t.type = Token::TT_UNKNOWN;
    t.contents = rest;
    skip = rest.size();
  }

  rest = rest.substr(skip);
  tokens.push_back(t);
}

void Tokenizer::skipWS() const
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

size_t Tokenizer::getOperator() const
{
  skipWS();
  if ( rest.empty() ) {
    return 0;
  }

  string op;
  for ( size_t n = 0 ; n < rest.size() ; ++n ) {
    char c = rest[n];
    if ( isalnum(c) || isspace(c) ) {
      break;
    }
    op += c;
  }

  return op.size();
}

size_t Tokenizer::getKeyword() const
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

size_t Tokenizer::getInteger() const
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

size_t Tokenizer::getString() const
{
  skipWS();
  if ( rest.empty() ) {
    return 0;
  }

  char const * data = rest.c_str();
  size_t count = 0;
  if ( *data == '"' ) {
    ++count; ++data;
    while ( *data != '"' ) {
      ++count; ++data;
    }
    ++count; ++data;
  }

  return count;
}

size_t Tokenizer::getSymbol() const
{
  skipWS();
  if ( rest.empty() ) {
    return 0;
  }

  char const * data = rest.c_str();
  size_t count = 0;
  if ( *data == ':' ) {
    ++count; ++data;
    while ( *data && ! isspace(*data) ) {
      ++count; ++data;
    }
  }

  return count;
}

size_t Tokenizer::getBoolean() const
{
  skipWS();
  if ( rest.size() < 2 ) {
    return 0;
  }

  char const * data = rest.c_str();
  char const c = data[1];
  if ( data[0] == '@' && ( c == 't' || c == 'T' || c == 'f' || c == 'F' ) ) {
    return 2;
  }

  return 0;
}

