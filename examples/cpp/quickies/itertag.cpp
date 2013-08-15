
#include <iterator>
#include <iostream>
#include <set>
#include <list>
#include <map>

template <typename T>
void f(std::iterator<std::input_iterator_tag, T> i)
{
  std::cout << "input_iterator_tag" << std::endl;
}


template <typename T>
void f(std::iterator<std::output_iterator_tag, T> i)
{
  std::cout << "output_iterator_tag" << std::endl;
}


void f(std::forward_iterator_tag i)
{
  std::cout << "forward_iterator_tag" << std::endl;
}


void f(std::bidirectional_iterator_tag i)
{
  std::cout << "bidirectional_iterator_tag" << std::endl;
}


void f(std::random_access_iterator_tag i)
{
  std::cout << "random_access_iterator_tag" << std::endl;
}

template <typename X>
void f(X x)
{
  typename std::iterator_traits<X>::iterator_category cat;
  f(cat);
}

int main(int argc, char** argv)
{
  std::set<int> s;
  f(s.begin());

  std::list<int> l;
  f(l.begin());

  std::map<int,int> m;
  f(m.begin());

  int a[1];
  f(&a[0]);

  //  std::ostream_iterator<int> o(std::cout, ", ");
  //  f(o);

  return 0;
}
