#if ! defined(DebugFormatter_h)
#define DebugFormatter_h 1

#include <cstdio>
#include <string>

#include "Buffer.h"
#include "IsIterable.h"

template<typename T>
class NullFormatter
{
public:
  void makeHeader(char * buf, char const ** & headers)
  {
    // do nothing
  }

  void format(Buffer & buf, T const &) 
  {
    // do nothing
  }
};

template<typename T>
class EolFormatter
{
public:
  void makeHeader(char * buf, char const ** & headers)
  {
    // do nothing
  }

  void format(Buffer & buf, T const &) 
  {
    buf.writeData();
  }
};

void makeHeader(char * buf, char const ** & headers, char const * fmt)
{
  char const * in;
  if ( headers == 0 || *headers == 0 ) {
    in = "header";
  }
  else {
    in = *headers++;
  }

  char t[32];
  sprintf(t, fmt, in);
  strcat(buf, t);
}

template<typename T>
class ItemFormatter
{
public:
  virtual ~ItemFormatter()
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    ::makeHeader(buf, headers, "%20s  ");
  }

  void format(Buffer & buf, T const &)
  {
    char t[32];
    sprintf(t, "%20s  ", "unknown type");
    buf.append(t);
  }
};

template<>
class ItemFormatter<int>
{
public:
  virtual ~ItemFormatter()
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    ::makeHeader(buf, headers, "%10s  ");
  }

  void format(Buffer & buf, int i)
  {
    char t[32];
    sprintf(t, "%10d  ", i);
    buf.append(t);
  }
};


template<>
class ItemFormatter<double>
{
public:
  virtual ~ItemFormatter()
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    ::makeHeader(buf, headers, "%18s  ");
  }

  void format(Buffer & buf, double d)
  {
    char t[32];
    sprintf(t, "%18f  ", d);
    buf.append(t);
  }
};

template<>
class ItemFormatter<float> : public ItemFormatter<double>
{
};


template<>
class ItemFormatter<std::string>
{
public:
  virtual ~ItemFormatter()
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    ::makeHeader(buf, headers, "%20s  ");
  }

  void format(Buffer & buf, std::string const & s)
  {
    char t[32];
    snprintf(t, 21, "%-20s", s.c_str());
    t[21] = t[22] = ' ';
    t[23] = '\0';
    buf.append(t);
  }
};

template<typename T, typename F>
class ContainerFormatter
{
public:
  typedef T                                       container_type;
  typedef F                                       item_formatter_type;
  typedef typename container_type::const_iterator iter_type;

  ContainerFormatter(F & _f) 
    : fmt(_f)
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    fmt.makeHeader(buf, headers);
  }

  void format(Buffer & buf, container_type const & c)
  {
    for ( iter_type iter = c.begin() ; iter != c.end() ; ++iter ) {
      buf.pushState();
      fmt.format(buf, *iter);
      buf.popState();
    }
  }

private:
  item_formatter_type fmt;
};


template<typename T, typename E>
class StructFormatter : public ItemFormatter<E>
{
public:
  typedef T      value_type;
  typedef E      element_type;
  typedef E T::* pmv_type;

  StructFormatter(pmv_type _pmv)
    : pmv(_pmv)
  {
  }
  
  void format(Buffer & buf, T const & t) 
  {
    element_type e = t.*pmv;
    ItemFormatter<E>::format(buf, e);
  }

private:
  pmv_type pmv;
};


template<typename V, typename H, typename T>
class DebugFormatter
{
public:
  typedef H car_type;
  typedef T cdr_type;
  typedef V value_type;

  DebugFormatter()
  {
  }

  DebugFormatter(car_type & h, cdr_type & t)
    : head(h)
    , tail(t)
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    head.makeHeader(buf, headers);
    tail.makeHeader(buf, headers);
  }

  void format(Buffer & buf, value_type const & v)
  {
    buf.pushState();
    head.format(buf, v);
    tail.format(buf, v);
    buf.popState();
  }

private:
  car_type head;
  cdr_type tail;
};

template<typename V, typename H, typename T>
class ContainerFormatter2
{
public:
  typedef          H                          car_type;
  typedef          T                          cdr_type;
  typedef          V                          value_type;
  typedef typename value_type::const_iterator iter_type;

  ContainerFormatter2()
  {
  }

  ContainerFormatter2(car_type & h, cdr_type & t)
    : head(h)
    , tail(t)
  {
  }

  void makeHeader(char * buf, char const ** & headers)
  {
    head.makeHeader(buf, headers);
    tail.makeHeader(buf, headers);
  }

  void format(Buffer & buf, value_type const & v)
  {
    for ( iter_type iter = v.begin() ; iter != v.end() ; ++iter ) {
      buf.pushState();
      head.format(buf, *iter);
      tail.format(buf, *iter);
      buf.popState();
    }
  }

private:
  car_type head;
  cdr_type tail;
};

#endif
