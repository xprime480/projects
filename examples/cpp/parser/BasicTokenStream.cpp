// $Id: /home/I809989/test/cpp/parser/BasicTokenStream.cpp#1 $
// $DateTime: Mon Apr 18 10:02:56 2011 $

#include <string>
#include <stdexcept>

#include "Token.h"

#include "BasicTokenStream.h"

using namespace std;
using namespace parser;

/*********************** IMPLEMENTATION ***************************/

BasicTokenStream::BasicTokenStream(CharacterStream & chars)
  : TokenStream(chars)
{
}

/*************************************/

Token * BasicTokenStream::getNextToken()
{
  string buf;
  char c = skipws();
  if ( c == -1 ) {
    return 0;
  }

  buf += c;

  if ( isSymbolChar(c) ) {
    return tokenizeSymbol(buf);
  }
  else if ( isDigitChar(c) ) {
    return tokenizeNumeric(buf);
  }
  else if ( isQuoteChar(c) ) {
    return tokenizeText(c); 
  }
  else if ( isLeftChar(c) ) {
    return new Token(Token::TOKEN_LDELIM, buf);
  }
  else if ( isRightChar(c) ) {
    return new Token(Token::TOKEN_RDELIM, buf);
  }
  else if ( isOperChar(c) ) {
    return tokenizeOperator(buf);
  }
  else if ( isEol(c) ) {
    linenumber++;
    return new Token(Token::TOKEN_EOL, buf);
  }

  return new Token(Token::TOKEN_UNKNOWN, buf);
}

/*************************************/

bool BasicTokenStream::isLeftChar(char c) const
{
  return c == '(' || c == '[' || c == '{';
}

/*************************************/

bool BasicTokenStream::isRightChar(char c) const
{
  return c == ')' || c == ']' || c == '}';
}

/*************************************/

bool BasicTokenStream::isOperChar(char c) const
{
  return (c == '+' || c == '-' || c == '*' || c == '/' ||
	  c == '=' || c == '<' || c == '>' );
}

/*************************************/

Token * BasicTokenStream::tokenizeSymbol(std::string & buf)
{
  while ( char c = getc() ) {
    if ( isSymbolChar(c) || isDigitChar(c) ) {
      buf += c;
    }
    else {
      ungetc(c);
      break;
    }
  }
  
  return new Token(Token::TOKEN_SYM, buf);
}

/*************************************/

Token * BasicTokenStream::tokenizeNumeric(std::string & buf)
{
  Token::types type = Token::TOKEN_INT;
  while ( char c = getc() ) {
    if ( isDigitChar(c) ) {
      buf += c;
    }
    else if ( c == '.' ) {
      buf += c;
      type = Token::TOKEN_FLOAT;
      break;
    }
  }

  if ( type == Token::TOKEN_FLOAT ) {
    while ( char c = getc() ) {
      if ( isDigitChar(c) ) {
	buf += c;
      }
      else {
	break;
      }
    }
  }

  return new Token(type, buf);
}

/*************************************/

Token * BasicTokenStream::tokenizeText(char delim)
{
  string buf;
  bool terminated = false;
  while ( char c = getc() ) {
    if ( c == delim ) {
      terminated = true;
      break;
    }
    if ( isEol(c) ) {
      ungetc(c);
      throw new runtime_error("newline in literal string");
    }
    buf += c;
  }

  if ( ! terminated ) {
    throw new runtime_error("end of file in literal string");
  }

  return new Token(Token::TOKEN_TEXT, buf);
}

/*************************************/

Token * BasicTokenStream::tokenizeOperator(std::string & buf)
{
  string b2(buf);
  char c = getc();
  b2 += c;
  
  if ( b2 == "+=" || b2 == "-=" || b2 == "/=" || b2 == "*=" ||
       b2 == "<=" || b2 == ">=" || b2 == "==" || b2 == ">>" ||
       b2 == "<<" ) {
    return new Token(Token::TOKEN_OPER, b2);
  }
  
  ungetc(c);
  return new Token(Token::TOKEN_OPER, buf);
}
