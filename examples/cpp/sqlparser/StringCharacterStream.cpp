// $Id: /home/I809989/test/cpp/parser/StringCharacterStream.cpp#1 $
// $DateTime: Mon Apr 18 12:08:11 2011 $

#include <cstring>

#include "StringCharacterStream.h"

using namespace std;
using namespace parser;

StringCharacterStream::StringCharacterStream(char const * _c)
{
  if ( _c ) {
    buf = strdup(_c);
  }
  else {
    buf = new char[1];
    buf[0] = '\0';
  }
}
