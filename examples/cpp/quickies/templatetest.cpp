

#include <map>
#include <set>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>

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

/*
 * Struct to format keys
 */
struct KeyFormatter
{
public:
  static char const * fmt;
  static char const * hdr;

  void operator()(key_type const & key) const
  {
    fprintf(stdout, fmt, key.c_str());
  }
};
char const * KeyFormatter::fmt = "%10s  ";
char const * KeyFormatter::hdr = "%10s  ";

template<typename T>
struct ValueFormatter
{
public:
  static char const * fmt;
  static char const * hdr;

  void operator()(T const & v) const
  {
    fprintf(stdout, fmt, "unknown value type");
  }
};
template<typename T> char const * ValueFormatter<T>::fmt = "%20s  ";
template<typename T> char const * ValueFormatter<T>::hdr = "%20s  ";


template<>
struct ValueFormatter<int>
{
public:
  static char const * fmt;
  static char const * hdr;

  void operator()(int v) const
  {
    fprintf(stdout, fmt, v);
  }
};
char const * ValueFormatter<int>::fmt = "%10d  ";
char const * ValueFormatter<int>::hdr = "%10s  ";

template<>
struct ValueFormatter<double>
{
public:
  static char const * fmt;
  static char const * hdr;

  void operator()(double v) const
  {
    fprintf(stdout, fmt, v);
  }
};
char const * ValueFormatter<double>::fmt = "%12.4g|  ";
char const * ValueFormatter<double>::hdr = "%12s|  ";

/*
 * Base case for formatting a row of data with keys
 */
template<typename T, bool NMC>
class FormatHelper
{
public:
  typedef T                          value_type;
  typedef ValueFormatter<value_type> formatter_type;

  void execute(value_type const & value, 
	       key_list_type const & keys)
  {
    std::for_each(keys.begin(), keys.end(), kf);
    f(value);
    fprintf(stdout, "\n");
  }

private:
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
class Formatter
{
public:
  typedef T value_type;

  void execute(value_type const & v, std::string const & header)
  {
    std::cout << header << std::endl;
    key_list_type keys;
    impl.execute(v, keys);
  }

private:
  FormatHelper<T, IsNonMapContainer<T>::value> impl;
};

template<typename T>
char const * makeHeader(char const * name)
{
  static char buf[32];
  char const * hdr = ValueFormatter<T>::hdr;
  sprintf(buf, hdr, name);
  return buf;
}

struct HeaderBuilder
{
public:
  HeaderBuilder & addKey(char const * name)
  {
    char buf[64];
    sprintf(buf, KeyFormatter::hdr, name);
    hdr << buf;
    return *this;
  }

  template<typename T>
  HeaderBuilder & addValue(char const * name)
  {
    
    hdr << makeHeader<T>(name);
    return *this;
  }

  char const * header() const
  {
    return hdr.str().c_str();
  }

  void reset()
  {
    hdr.str("");
  }
  

private:
  std::stringstream hdr;
};

std::vector<std::string> split(std::string const & input, char splitter)
{
  std::vector<std::string> values;
  size_t lim = input.size();
  std::string temp = "";

  for ( size_t pos = 0 ; pos < lim ; ++pos ) {
    char ch = input.at(pos);
    if ( ch == splitter ) {
      values.push_back(temp);
      temp = "";
    }
    else {
      temp += ch;
    }
  }

  values.push_back(temp);
  return values;
}

struct Point
{
  Point(float _x, float _y) : x(_x), y(_y) {}
  float x,y;
};

template<>
struct ValueFormatter<Point>
{
public:
  static char const * fmt;
  static char const * key;

  void operator()(Point p) const
  {
    fprintf(stdout, fmt, p.x, p.y);
  }

  static const char * buildFmt() 
  {
    static char buf[32];
    strcpy(buf, ValueFormatter<double>::fmt);
    strcat(buf, ValueFormatter<double>::fmt);
    return buf;
  }

  static const char * buildKey() 
  {
    static char buf[32];
    strcpy(buf, ValueFormatter<double>::hdr);
    strcat(buf, ValueFormatter<double>::hdr);
    return buf;
  }
};
char const * ValueFormatter<Point>::fmt = ValueFormatter<Point>::buildFmt();
char const * ValueFormatter<Point>::key = ValueFormatter<Point>::buildKey();

template<>
char const * makeHeader<Point>(char const * name)
{
  static HeaderBuilder hdr;
  hdr.reset();
  std::vector<std::string> h = split(name, ';');
  hdr.addValue<double>(h.size() > 0 ? h[0].c_str() : "X");
  hdr.addValue<double>(h.size() > 1 ? h[1].c_str() : "Y");
  return hdr.header();
}

template<typename T>
void runtest(T const & t, std::string header)
{
  Formatter<T> tester;
  tester.execute(t, header);
  std::cout << std::endl << std::endl;
}

int main(int argc, char ** argv)
{
  HeaderBuilder hdr;

  int i = 0;
  hdr.addValue<int>("Test");
  runtest(i, hdr.header());

  std::map<int, int> m;
  m[1] = 2;
  m[3] = 7;
  hdr.reset();
  hdr.addKey("N");
  hdr.addValue<int>("Val");
  runtest(m, hdr.header());

  std::set<int> s;
  s.insert(7);
  s.insert(-134);
  hdr.reset();
  hdr.addValue<int>("Set Val");
  runtest(s, hdr.header());

  std::vector<int> vi(s.begin(), s.end());
  hdr.reset();
  hdr.addValue<int>("Vec Val");
  runtest(vi, hdr.header());

  std::vector<Point> vp;
  vp.push_back(Point(1.23, 4.56));
  vp.push_back(Point(7.00, 0.01));
  hdr.reset();
  hdr.addValue<Point>("X;Y");
  runtest(vp, hdr.header());

  return 0;
}
