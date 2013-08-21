// $Id: /home/I809989/test/cpp/parser/TokenStream.cpp#1 $
// $DateTime: Mon Apr 18 07:43:16 2011 $

#include <stdexcept>
#include <ctype.h>

#include "CharacterStream.h"

#include "TokenStream.h"

using namespace std;
using namespace parser;

TokenStream::TokenStream(CharacterStream & _c)
  : chars(_c)
  , pos(-1)
  , linenumber(1)
{
}

TokenStream::~TokenStream()
{
  
}

Token * TokenStream::get() const
{
  if ( pos >= 0 && pos < tokens.size() ) {
    return tokens.at(pos);
  }

  return 0;
}

void TokenStream::forward()
{
  ++pos;
  while ( tokens.size() <= pos ) {
    tokens.push_back(getNextToken());
  }
}

void TokenStream::back()
{
  if ( pos <= 0 ) {
    throw runtime_error("TokenStream::back: Already at beginning of token stream");
  }
  --pos;
}

TokenStream::state_type TokenStream::getState() const
{
  return pos;
}

void TokenStream::setState(state_type state)
{
  if ( state == pos ) {
    return;
  }
  if ( state < 0 ) {
    pos = 0;			// there was an intervening read...
  }
  else if ( state < tokens.size() ) {
    pos = state;
  }
  else {
    throw runtime_error("TokenStream::setState: invalid state");
  }
}


char TokenStream::peek() const
{
  return chars.peek();
}

char TokenStream::getc()
{
  return chars.getc();
}

void TokenStream::ungetc(char c)
{
  return chars.ungetc(c);
}

bool TokenStream::eof() const
{
  return chars.eof();
}

bool TokenStream::isSymbolChar(char c)
{
  return isalpha(c) || c == '_';
}

bool TokenStream::isDigitChar(char c)
{
  return isdigit(c);
}

bool TokenStream::isQuoteChar(char c)
{
  return c == '\"' || c == '\'';
}

bool TokenStream::isEol(char c)
{
  return c == '\n';
}

bool TokenStream::isSpace(char c)
{
  return isspace(c) && ! isEol(c);
}

char TokenStream::skipws()
{
  while ( char c = getc() ) {
    if ( ! isSpace(c) ) {
      return c;
    }
  }
  return -1;
}

NullTokenStream::NullTokenStream(CharacterStream & _c)
  :TokenStream(_c)
{
}

Token * NullTokenStream::getNextToken()
{
  return 0;
}


