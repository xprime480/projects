
#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "range.h"
#include "streamutils.h"

using std::pair;
using std::vector;
using std::set;
using std::multiset;
using std::map;
using std::cout;
using std::endl;

template <typename T, typename F>
void f(const T & t, F & fn)
{
  for ( auto i : t ) {
    fn(i);
  }
  cout << endl;
}

template <typename T>
void display(const T & t)
{
  auto gg = [] (int i) { cout << i << ' '; };
  f(t, gg);
  cout << endl;
}

void test1()
{
  vector<int> vi;

  auto x = { 1, 3, -1, 777, 3};
  auto ff = [&vi] (int i) { vi.push_back(i); };

  f(vector<int>(x), ff);
  f(set<int>(x), ff);
  f(multiset<int>(x), ff);

  display(vi);
}

template <typename T, typename KFN, typename IFN>
void partition_by(const T & data, KFN key_fn, IFN insert_fn)
{
  for ( auto value : data ) {
    auto key = key_fn(value);
    insert_fn(key, value);
  }
}

using vectype = vector<int>;

void test2a(const vectype & vi)
{
  map<int, vectype> groups;
  auto keep = { 0, 2, 4 };
  for ( auto i : keep ) {
    groups[i] = vectype{};
  }

  int n { 11 };
  auto mod_n = [&n] (int i) { return i%n; };
  auto insert_by_key = [&groups] (int key, int val) {
    if (groups.find(key) != groups.end()) {
      groups[key].push_back(val);
    }
  };
  partition_by(vi, mod_n, insert_by_key);

  for ( auto i : keep ) {
    cout << i << ": ";
    display(groups[i]);
  }
}

bool isprime(int i)
{
  if ( i < 2 ) {
    return false;
  }

  for ( int x = 2 ; x * x <= i ; ++x ) {
    if ( i%x == 0 ) {
      return false;
    }
  }

  return true;
}

void test2b(const vectype & vi)
{
  vectype primes{};

  auto insert_primes = [&primes] (bool prime, int val) {
    if (prime) {
      primes.push_back(val);
    }
  };
  partition_by(vi, isprime, insert_primes);

  display(primes);
}

void test2()
{
  Range<int> basic(1,100,1);
  vectype vi = collect(basic);

  test2a(vi);
  test2b(vi);
}

int foo(int v)
{
  return v;
}

enum class F { A = 1, B = 2 };

int foo(F f)
{
  return static_cast<int>(f);
}


template <typename OS>
OS & operator<<(OS & os, F const & f)
{
  switch ( f ) {
  case F::A :
    return os << "F::A";
    break;
  case F::B :
    return os << "F::B";
    break;
  }
  return os << "F error <" << static_cast<int>(f) << ">";
}

enum G { X = 1, Y = 2 };

void test3()
{
  F f1{F::A};
  F f2{F::B};
  F f3{};
  cout << f1 << " " << f2 << " " << f3 << endl;

  G g1{X};
  G g2{};
  cout << g1 << " " << g2 << endl;

  cout << foo(f3) << " " << foo(g1) << endl;

  using maptype = map<F, int>;
  maptype m { {f1,1}, {f3,7} };
  cout << m.size() << endl;
}

void syntaxtest(int argc, char ** argv)
{
  test1();
  cout << endl;
  test2();
  test3();
}
