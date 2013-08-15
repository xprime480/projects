
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <numeric>

//

double v[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
double w[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

template <typename T>
struct power : public std::unary_function<T, T>
{
  power(T e) : expt(e) {}
  T operator()(T const & b) { return std::pow(b, expt); }
private:
  T expt;
};

template <typename Iter>
void dump(Iter from, Iter to, std::ostream & os = std::cout)
{
  typedef typename std::iterator_traits<Iter>::value_type value_type;
  std::ostream_iterator<value_type> strm(os, " ");
  std::copy(from, to, strm);
  os << "\n";
}

int main(int argc, char ** argv)
{
  std::transform(v, v + 5, w, power<double>(5));
  dump(v, v + 5);
  dump(w, w + 5);

  std::random_shuffle(v, v + 5);
  std::cout << *std::max_element(v, v + 5) << "\n";
}
