#include <map>
#include <set>
#include <iostream>
#include <iterator>

template <typename T, typename S>
T extract(S const & data, int const & code)
{
  throw "extract: unimplemented";
}


/*!
  \brief
  
  \param
  
  \return
*/
template <typename T, typename S>
class cache_key
{
public:
  typedef T value_type;
  typedef S source_type;
  typedef int extractor_type;	// really just a code

  template <typename U>
  cache_key(extractor_type e, U const & par)
    : extractor(e)
    , attr_1(par.attr_1)
  {
  }
  
  int getAttr_1() const
  {
    return attr_1;
  }
  
  extractor_type getExtractor() const
  {
    return extractor;
  }

private:
  int attr_1;
  extractor_type extractor;
};

template <typename T, typename S>
bool operator< (cache_key<T,S> const & x, cache_key<T,S> const & y)
{
  typedef typename cache_key<T,S>::extractor_type extractor_type;

  extractor_type xx = x.getExtractor();
  extractor_type yx = y.getExtractor();

  if ( xx < yx ) {
    return true;
  }
  if ( yx < xx ) {
    return false;
  }

  return x.getAttr_1() < y.getAttr_1();
}


/*!
  \brief
  
  \param
  
  \return
*/
template <typename T, typename S>
class MetaCache
{
public:
  typedef T                         value_type;
  typedef S                         source_type;
  typedef cache_key<T, S>           key_type;
  typedef std::set<value_type>      set_type;
  typedef typename std::map<key_type, set_type> map_type;
  typedef typename key_type::extractor_type extractor_type;

private:
  static map_type meta_map;
  
public:
  template <typename U>
  MetaCache(extractor_type e, U const & par)
    : extractor(e)
    , key(e, par)
  {
    meta_map[key];		// create an empty map if none exists
  }

  void put(S const & source)
  {
    meta_map[key].insert(extract(source, extractor));
  }

  set_type get() const
  {
    typename map_type::const_iterator pos = meta_map.find(key);
    return pos->second;
  }

private:
  extractor_type extractor;
  key_type       key;
};

template <typename T, typename S> 
typename MetaCache<T, S>::map_type 
MetaCache<T, S>::meta_map;


/*!
  \brief
  
  \param
  
  \return
*/
class TestClass1
{
public:
  enum {
    MEMBER_D,
    MEMBER_I,
    MEMBER_J
  };

  double d;
  int    i;
  int    j;
};

template int extract<int, TestClass1>(TestClass1 const & data, int const & i);

int extract(TestClass1 const & data, int const & i)
{
  switch ( i ) {
  case TestClass1::MEMBER_I:
    return data.i;
  case TestClass1::MEMBER_J:
    return data.j;
  }
  throw "unknown member";
}

/*!
  \brief
  
  \param
  
  \return
*/
class TestClass2
{
public:
  enum {
    MEMBER_J,
    MEMBER_X
  };

  int    j;
  char * x;
};

/*!
  \brief
  
  \param
  
  \return
*/
struct AttrClass1
{
  int attr_1;
};

int main(int, char **)
{
  typedef MetaCache<int, TestClass1> cache_type;
  typedef cache_type::set_type set_type;

  AttrClass1 attrs1;
  attrs1.attr_1 = 23;
  cache_type mc1(TestClass1::MEMBER_I, attrs1);
  cache_type mc2(TestClass1::MEMBER_J, attrs1);

  attrs1.attr_1 = 74;
  cache_type mc3(TestClass1::MEMBER_J, attrs1);

  TestClass1 data1;
  data1.i = 238; 
  data1.j = 823;
  mc1.put(data1);
  mc2.put(data1);
  
  data1.i = 777;
  data1.j = 123;
  mc1.put(data1);
  mc3.put(data1);

  set_type values;

  values = mc2.get();
  std::copy(values.begin(), values.end(), 
	    std::ostream_iterator<int>(std::cout, "\n"));
}
