// $Id: /home/I809989/test/cpp/parser.v2/Expression.cpp#1 $
// $DateTime: Tue Apr 19 10:51:49 2011 $

#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "Expression.h"

using namespace std;
using namespace parser;

Expression::Expression(bool b)
  : tag(Expression::EV_BOOL)
{
  value.b = b;
}

Expression::Expression(int i)
  : tag(Expression::EV_INT)
{
  value.i = i;
}

Expression::Expression(double d)
  : tag(Expression::EV_DOUBLE)
{
  value.d = d;
}

Expression::Expression(char const * c)
  : tag(Expression::EV_STR)
{
  
  value.c = new char[strlen(c) + 1];
  strcpy(value.c, c);
}

Expression::Expression()
  : tag(Expression::EV_LIST)
{
  value.v = new vofe;
}


Expression::Expression(Expression const & e)
{
  this->tag = e.tag;
  size_t s = 0;
  switch ( e.tag ) {
  case EV_BOOL:
    value.b = e.value.b;
    break;
  case EV_INT:
    value.i = e.value.i;
    break;
  case EV_DOUBLE:
    value.d = e.value.d;
    break;
  case EV_STR:
    value.c = new char[e.size() + 1];
    strcpy(value.c, e.value.c);
    break;
  case EV_LIST:
    s = e.size();
    value.v = new vofe;
    for ( size_t i = 0 ; i < s ; ++i ) {
      value.v->push_back(e.nth(i));
    }
    break;
  default:
    throw runtime_error("Expression: Unknown type tag");
  }
}

Expression & Expression::operator=(Expression const & e)
{
  if ( this != &e ) {
    Expression temp(e);
    swap(tag,   temp.tag);
    swap(value, temp.value);
  }
  return *this;
}

Expression::~Expression()
{
  if ( tag == EV_STR ) {
    delete[] value.c;
    value.c = NULL;
  }
  else if ( tag == EV_LIST ) {
    delete value.v;
    value.v = NULL;
  }
}

Expression::operator bool() const
{
  switch ( tag ) {
  case EV_BOOL:
    return value.b;
    break;
  case EV_INT:
    return value.i != 0;
    break;
  case EV_DOUBLE:
    return value.d != 0.0;
    break;
  case EV_STR:
    return value.c[0] != '\0';
    break;
  case EV_LIST:
    return size() > 0;
    break;
  default:
    throw runtime_error("Expression: Unknown type tag");
  }
}

Expression::operator int() const
{
  switch ( tag ) {
  case EV_BOOL:
    return value.b ? 1 : 0;
    break;
  case EV_INT:
    return value.i;
    break;
  case EV_DOUBLE:
    return (int) value.d;
    break;
  case EV_STR: case EV_LIST:
    return (int) size();
    break;
  default:
    throw runtime_error("Expression: Unknown type tag");
  }
}

Expression::operator double() const
{
  switch ( tag ) {
  case EV_BOOL:
    return value.b ? 1.0 : 0.0;
    break;
  case EV_INT:
    return (double) value.i;
    break;
  case EV_DOUBLE:
    return value.d;
    break;
  case EV_STR: case EV_LIST:
    return (double) size();
    break;
  default:
    throw runtime_error("Expression: Unknown type tag");
  }
}


Expression::operator char const *() const
{
  static char buf[2000];
  switch ( tag ) {
  case EV_BOOL:
    strcpy(buf, value.b ? "True" : "False");
    break;
  case EV_INT:
    sprintf(buf, "%d", value.i);
    break;
  case EV_DOUBLE:
    sprintf(buf, "%f", value.d);
    break;
  case EV_STR:
    strncpy(buf, value.c, 1999);
    break;
  case EV_LIST:
    sprintf(buf, "List of size %ld", (long) size());
    break;
  default:
    throw runtime_error("Expression: Unknown type tag");
  }

  return buf;
}

void Expression::addText(char const * c)
{
  if ( tag == EV_STR ) {
    size_t s1 = strlen(value.c);
    size_t s2 = strlen(c);
    char * temp = new char[s1 + s2 + 1];
    strcpy(temp, value.c);
    strcpy(temp+s1, c);
    swap(temp, value.c);
    delete[] temp;
  }
  else {
    throw runtime_error("Expression: Adding text to a non-string");
  }
}

void Expression::append(Expression const & e)
{
  if ( tag == EV_LIST ) {
    value.v->push_back(e);
  }
  else {
    throw runtime_error("Expression: Appending to a non-list");
  }
}

size_t Expression::size() const
{
  if ( tag == EV_LIST ) {
    return value.v->size();
  }
  else {
    return 1;
  }
}

Expression const & Expression::nth(size_t i) const
{
  if ( tag == EV_LIST ) {
    if ( size() > i ) {
      return value.v->at(i);
    }
    else {
      throw runtime_error("Expression: Index out of range");      
    }
  }
  else {
    throw runtime_error("Expression: Indexing a non-list");
  }

  /* unreachable */
  throw runtime_error("Expression: Unreachable end of function");
}

Expression & Expression::nth(size_t i)
{
  if ( tag == EV_LIST ) {
    if ( size() > i ) {
      return value.v->at(i);
    }
    else {
      throw runtime_error("Expression: Index out of range");      
    }
  }
  else {
    throw runtime_error("Expression: Indexing a non-list");
  }

  /* unreachable */
  throw runtime_error("Expression: Unreachable end of function");
}

ostream & Expression::print(ostream & os) const
{
  if ( tag == EV_LIST ) {
    size_t n = size();
    if ( n == 0 ) {
      os << "nil";
    }
    else {
      os << "(" << nth(0);
      for ( size_t i = 1 ; i < n ; ++i ) {
	os << " " << nth(i);
      }
      os << ")";
    }
  }
  else {
    os << ((char const *) (*this));
  }

  return os;
}

Expression parser::nil(false);

std::ostream & operator<<(std::ostream & os, parser::Expression const & e)
{
  return e.print(os);
}


