
#include <iostream>
#include <map>

using namespace std;

const int x { 7 };

class X
{
public:
  void foo()
  {
    char a[x];
    cout << sizeof(a) << endl;
  }
  static const int x = 22;
};

template <typename V, typename K = int>
class Z : private map<K, V>
{
private:
  using impl_type = map<K,V>;
  using iter_type = typename impl_type::iterator;
  using const_iter_type = typename impl_type::const_iterator;

public:
  bool put(K const & key, V const & val)
  {
    using value_type = typename impl_type::value_type;
    using insert_info_type = pair<bool, iter_type>;
    const value_type insert_value { key, val };
    auto info = this->insert(insert_value);
    return info.second;
  };

  bool has(K const & key) const
  {
    const_iter_type loc = this->find(key);
    return loc != this->end();
  };

  V const & get(K const & key) const
  {
    if ( ! has(key) ) {
      throw 2;
    }
    const_iter_type loc = this->find(key);
    return loc->second;
  };

  V & get(K const & key)
  {
    if ( ! has(key) ) {
      throw 2;
    }
    iter_type loc = this->find(key);
    return loc->second;
  }

private:
};

int scopetest(int argc, char ** argv)
{
  cout << x << endl;
  const int x { 1 }; 
  cout << x << endl;
  {
    cout << x << endl;
    const int x { 2 };
    cout << x << endl;
  }
  cout << x << endl;

  X cl_x;
  cl_x.foo();

  Z<int> z;
  z.put(2,3);
  cout << boolalpha;
  cout << z.has(2) << endl;
  cout << z.has(3) << endl;
  cout << z.get(2) << endl;
}
