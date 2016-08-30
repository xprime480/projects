#include <vector>
#include <memory>
#include <iostream>

using std::vector;
using std::initializer_list;
using std::cout;
using std::endl;
using std::boolalpha;

namespace {
  class B {};
  class D1 : public B {};
  class D2 : public B {};
}

using B_ptr = std::shared_ptr<B>;

template <typename T>
vector<T> f(initializer_list<T> ts)
{
  return vector<T>(ts);
}

struct H
{
  H() : counter(0) {}
  ~H() { cout << "H's count is " << counter << endl; }
  template <typename T>
  bool aornotb(const T & a, const T & b)
  {
    counter++;
    if ( a ) return true;
    if ( b ) return false;
    return true;
  }
private:
  size_t counter;
};

template <>
bool H::aornotb<bool>(const bool & a, const bool & b)
{
  counter *= 2;
  return true;
}

template <typename O, typename C, typename... Rest>
bool componentwise_less(const O & o1, const O & o2, C getter, Rest... rest)
{
  auto v1 = o1.*getter;
  auto v2 = o2.*getter;
  if ( v1 != v2 ) {
    return v1 < v2;
  }

  return componentwise_less(o1, o2, rest...);
}

template <typename O, typename C>
bool componentwise_less(const O & o1, const O & o2, C getter)
{
  auto v1 = o1.*getter;
  auto v2 = o2.*getter;
  return v1 < v2;
}

template <typename O>
bool componentwise_less(const O & o1, const O & o2)
{
  return false;
}

struct S
{
  int i1;
  int i2;
  double d1;
};


int deducetest(int argc, char ** argv)
{
  vector<B_ptr> g;
  g.push_back(B_ptr(new D1()));
  g.push_back(B_ptr(new D2()));

  auto h = f(initializer_list<B_ptr>{ B_ptr(new D1()), B_ptr(new D2()), B_ptr(new D1()) });
  auto i = f({ new D1() });

  H ho;
  cout << boolalpha;
  cout << ho.aornotb(1, 2) << endl;
  cout << ho.aornotb((H*)nullptr, &ho) << endl;
  cout << ho.aornotb(false, true) << endl;

  S s1 { 1, 2, 7.5 };
  S s2 { 2, 1, 0.0 };
  S s3 { 1, 2, 6.5 };
  cout << "Scmp1: " << componentwise_less(s1, s2) << endl;
  cout << "Scmp2: " << componentwise_less(s1, s2, &S::i1) << endl;
  cout << "Scmp3: " << componentwise_less(s1, s3, &S::i1, &S::i2, &S::d1) << endl;

  cout << "done" << endl;
}
