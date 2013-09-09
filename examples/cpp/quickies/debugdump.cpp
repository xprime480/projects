#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/**
Non compiling code
 **/

/*
 * key types
 */
typedef std::string           key_type;
typedef std::vector<key_type> key_list_type;

/*
 * Helper template for determining if a typename represents a 
 * container that is not a map.
 */
template <typename V>
struct IsNonMapContainer
{ 
  static bool const value = false;
};

template <typename V>
struct IsNonMapContainer<std::set<V> >
{
  static bool const value = true;
};

template <typename V>
struct IsNonMapContainer<std::vector<V> >
{
  static bool const value = true;
};

template <typename V>
struct IsNonMapContainer<std::list<V> >
{
  static bool const value = true;
};

std::string makeHeader(char const * fmt, 
		       char const ** names)
{
  std::stringstream s;
  char buf[20];
  while ( names && *names ) {
    sprintf(buf, fmt, *names);
    s << buf;
    ++names;
  }
  return s.str();
}

/*
 * Struct to format keys
 */
struct KeyFormatter
{
public:
  static char const * valFormat()
  {
    return "%10s  ";
  }

  static char const * hdrFormat()
  {
    return valFormat();
  }

  void operator()(key_type const & key) const
  {
    fprintf(stdout, valFormat(), key.c_str());
  }

  static std::string makeHeader(char const ** names)
  {
    return ::makeHeader(hdrFormat(), names);
  }
};

template<typename T>
struct ValueFormatter
{
public:
  static char const * valFormat()
  {
    return "%20s  ";
  }

  static char const * hdrFormat()
  {
    return valFormat();
  }

  void operator()(T const & v) const
  {
    fprintf(stdout, valFormat(), "unknown value type");
  }

  static std::string makeHeader(char const ** names)
  {
    return ::makeHeader(hdrFormat(), names);
  }
};

template<>
struct ValueFormatter<int>
{
public:
  static char const * valFormat()
  {
    return "%10d  ";
  }

  static char const * hdrFormat()
  {
    return "%10s  ";
  }

  void operator()(int v) const
  {
    fprintf(stdout, valFormat(), v);
  }

  static std::string makeHeader(char const ** names)
  {
    return ::makeHeader(hdrFormat(), names);
  }
};

template<>
struct ValueFormatter<double>
{
public:
  static char const * valFormat()
  {
    return "%12.4g  ";
  }

  static char const * hdrFormat()
  {
    return "%12s  ";
  }

  void operator()(double v) const
  {
    fprintf(stdout, valFormat(), v);
  }

  static std::string makeHeader(char const ** names)
  {
    return ::makeHeader(hdrFormat(), names);
  }
};

template<typename K, typename V>
struct ValueFormatter<std::map<K, V> >
{
public:
  static std::string makeHeader(char const ** names)
  {
    return ValueFormatter<V>::makeHeader(names);
  }
};

class NullFormatHelper
{
};

template<typename M, typename Head, typename Tail>
struct MapFormatter
{
};


/*
 * Base case for formatting a row of data with keys
 */
template<typename T, bool NMC>
class FormatHelper
{
public:
  typedef T                          value_type;
  typedef ValueFormatter<value_type> formatter_type;

  FormatHelper(char const ** keys, char const ** values)
    : header(ValueFormatter<T>::makeHeader(keys&&*keys
					   ? *keys
					   : (values&&*values
					      ? *values
					      : "Header")))
  {
  }

  void execute(value_type const & value, 
	       key_list_type const & keys)
  {
    std::for_each(keys.begin(), keys.end(), kf);
    f(value);
    fprintf(stdout, "\n");
  }

private:
  char const * header;

  KeyFormatter   kf;
  formatter_type f;
};

template <typename K, typename V>
class FormatHelper<std::map<K,V>, false>
{
public:
  typedef typename std::map<K,V>            map_type;
  typedef typename map_type::mapped_type    value_type;
  typedef typename map_type::const_iterator iter_type;
  typedef          ValueFormatter<V>        formatter_type;

  void execute(map_type const & value, key_list_type const & keys)
  {
    key_list_type k(keys);
    for ( iter_type i = value.begin() ; i != value.end() ; ++i ) {
      std::stringstream s;
      s << i->first;
      k.push_back(s.str());
      helper.execute(i->second, k);
      k.pop_back();
    }
  }

private:
  FormatHelper<value_type, IsNonMapContainer<value_type>::value>  helper;
  formatter_type formatter;
};

template <typename V>
class FormatHelper<V, true>
{
public:
  typedef          V                              container_type;
  typedef typename container_type::value_type     value_type;
  typedef typename container_type::const_iterator iter_type;

  void execute(container_type const & value, key_list_type const & keys)
  {
    for ( iter_type i = value.begin() ; i != value.end() ; ++i ) {
      helper.execute(*i, keys);
    }
  }
private:
  FormatHelper<value_type, IsNonMapContainer<value_type>::value>  helper;
};

template<typename T>
std::string makeHeader(char const ** names)
{
  return makeHeader(ValueFormatter<T>::hdrFormat(), names);
}

template<typename V, typename H, typename T>
class Formatter
{
public:
  typedef V value_type;
  typedef H head_type;
  typedef T tail_type;

  Formatter(T & t)
    : tail(t)
  {
  }

  void execute(value_type const & v)
  {
    std::cout << header << std::endl;
    key_list_type keys;
    impl.execute(v, keys);
  }

private:
  tail_type & tail;

  FormatHelper<T, IsNonMapContainer<T>::value> impl;
  std::string const header;

  std::string makeHeader(char const ** keys,
			 char const ** values)
  {
    std::stringstream s;
    s << KeyFormatter::makeHeader(keys);
    s << ValueFormatter<T>::makeHeader(values);
    return s.str();
  }
};



template<typename T>
char const * makeHeader(char const * name)
{
  static char buf[32];
  char const * hdr = ValueFormatter<T>::hdr;
  sprintf(buf, hdr, name);
  return buf;
}

struct Point
{
  Point(float _x, float _y) : x(_x), y(_y) {}
  float x,y;
};

void debugFormat(...)
{
  std::cout << "Can't help you for these types\n";
}

template<typename T>
struct FormatterProperties
{
  typedef NullFormatHelper                   head_type;
  typedef NullFormatHelper                   tail_type;
  typedef Formatter<T, head_type, tail_type> main_type;
};

template<typename K, typename V>
struct FormatterProperties<std::map<K, V> >
{
  typedef FormatHelper<K, false>                             head_type;
  typedef FormatHelper<V, IsNonMapContainer<V>::value>       tail_type;
  typedef MapFormatter<std::map<K, V>, head_type, tail_type> main_type;
};


template<typename K, typename V>
void debugFormat(std::map<K, V> const & t, 
		 char const ** keys, 
		 char const ** values)
{
  typedef FormatterProperties<std::map<K, V> > maker_type;
  typedef typename maker_type::head_type       head_type;
  typedef typename maker_type::tail_type       tail_type;
  typedef typename maker_type::main_type       main_type;

  head_type head(keys+0, values);
  tail_type tail(keys+1, values);
  main_type main(head, tail);
  main.execute(t);
  std::cout << std::endl << std::endl;
}

template<typename T, typename U, typename M1>
void debugFormat(T const & t, 
	     char const ** keys, 
	     char const ** values, 
	     M1 U::*m1)
{
#if 0
  Formatter<T> tester(keys, values);
  tester.execute(t);
  std::cout << std::endl << std::endl;
#endif
}

template<typename T, typename U, typename M1, typename M2>
void debugFormat(T const & t, 
		 char const ** headers, 
		 M1 U::*m1, 
		 M2 U::*m2)
{
#if 0
  Formatter<T> tester(keys, values, m1, m2);
  tester.execute(t);
  std::cout << std::endl << std::endl;
#endif
}

void test1()
{
  char const * hdrs[] = { "N", "Val", 0 };

  std::map<int, int> m;
  m[1] = 2;
  m[3] = 7;

  debugFormat(m, hdrs);
}

void test2()
{
  char const * hdrs[] = { "X", "Y", 0 };

  std::vector<Point> vp;
  vp.push_back(Point(1.23, 4.56));
  vp.push_back(Point(7.00, 0.01));

  debugFormat(vp, hdrs, &Point::x, &Point::y);
}

int main(int argc, char ** argv)
{
  test1();
#if 0
  test2();

  HeaderBuilder hdr;

  int i = 0;
  hdr.addValue<int>("Test");
  debugFormat(i, hdr.header());

  std::map<int, int> m;
  m[1] = 2;
  m[3] = 7;
  hdr.reset();
  hdr.addKey("N");
  hdr.addValue<int>("Val");
  debugFormat(m, hdr.header());

  std::set<int> s;
  s.insert(7);
  s.insert(-134);
  hdr.reset();
  hdr.addValue<int>("Set Val");
  debugFormat(s, hdr.header());

  std::vector<int> vi(s.begin(), s.end());
  hdr.reset();
  hdr.addValue<int>("Vec Val");
  debugFormat(vi, hdr.header());

  hdr.reset();
  hdr.addValue<Point>("X;Y");
  debugFormat(vp, hdr.header());
#endif

  return 0;
}
