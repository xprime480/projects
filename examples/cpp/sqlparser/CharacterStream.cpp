// $Id: /home/I809989/test/cpp/parser/CharacterStream.cpp#1 $
// $DateTime: Mon Apr 18 11:23:56 2011 $

#include "CharacterStream.h"

using namespace std;
using namespace parser;

CharacterStream::CharacterStream()
  : buf(0)
  , pos(0)
{
}

CharacterStream::~CharacterStream()
{
  delete[] buf;
}

string CharacterStream::debug() const
{
  string t("<");
  
  if ( ! buf ) {
    t += '>';
    return t;
  }
  size_t x = pos;
  while ( buf[x] ) {
    t += buf[x];
    ++x;
  }
  t += '>';
  if ( buf[x] ) {
    t.append("...");
  }

  return t;
}

char CharacterStream::peek() const
{
  if ( ! buf || ! buf[pos] ) {
    return -1;
  }
  return buf[pos];
}

char CharacterStream::getc()
{
  if ( ! eof() ) {
    ++pos;
    return buf[pos-1];
  }
  return -1;
}

void CharacterStream::ungetc(char c)
{
  if ( pos > 0 ) {
    --pos;
  }
}

bool CharacterStream::eof() const
{
  char c = peek();
  return c == -1;
}

void CharacterStream::reset()
{
  pos = 0;
}



NullCharacterStream::NullCharacterStream()
{
  buf = new char[1];
  buf[0] = '\0';
}
