
#include "tokenstream.h"

using std::string;

TokenStream::TokenStream()
  : bufp{0}
  , buf_sz{0}
  , ws(" \t\n\r")
{
}

Token TokenStream::operator()()
{
  skip_ws();

  string value;

  while ( true ) {
    if ( bufp == buf_sz ) {
      buf_sz = BUFSIZE;
      bufp = 0;
      this->fillBuffer(buffer, buf_sz);
      if ( 0 == buf_sz ) {
	break;
      }
    }

    auto c = buffer[bufp];
    if ( string::npos == ws.find(c) ) {
      value += c;
      bufp++;
    }
    else {
      break;
    }
  }

  if ( value.empty() ) {
    throw GeneratorException{};
  }

  return Token { value };
}  

void TokenStream::skip_ws()
{
  while ( true ) {
    if ( bufp == buf_sz ) {
      buf_sz = BUFSIZE;
      bufp = 0;
      this->fillBuffer(buffer, buf_sz);
      if ( 0 == buf_sz ) {
	break;
      }
    }

    auto c = buffer[bufp];
    if ( string::npos == ws.find(c) ) {
      break;
    }
    else {
      ++bufp;
    }
  }
}

