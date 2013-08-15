/*
 * Based on algorithms from:
 *
 * http://en.wikipedia.org/wiki/Continued_fraction
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

class ContinuedFraction
{
public:
  ContinuedFraction(double n, int places)
  {
    n = std::fabs(n);

    while ( n > 0 && places > 0 ) {
      int an = (int) std::floor(n);
      a.push_back(an);
      n = 1.0 / (n-an);
      --places;
    }

    init();
  }

  template <typename Iter>
  ContinuedFraction(Iter begin, Iter end)
    : a(begin, end)
  {
    init();
  }

  void computeAll() 
  {
    typedef data_type::const_iterator iter_type;
    int hk_index = 2;
    for ( iter_type iter = a.begin() ; iter != a.end() ; ++iter ) {
      int hn = *iter * h[hk_index - 1] + h[hk_index - 2];
      int kn = *iter * k[hk_index - 1] + k[hk_index - 2];
      ++hk_index;

      h.push_back(hn);
      k.push_back(kn);
    }
  }

  void showConvergents() const
  {
    int const hk_end   = h.size();

    for ( int hk_index = 2 ; hk_index < hk_end ; ++hk_index ) {
      std::cout << h[hk_index] << " / " << k[hk_index] << std::endl;
    }
  }

  void showSeries() const
  {
    data_type::const_iterator iter = a.begin();
    std::cout << *iter  << "; ";
    ++iter;

    for ( /**/ ; iter != a.end() ; ++iter ) {
      std::cout << *iter << ", ";
    }

    std::cout << std::endl;
  }

protected:
private:
  typedef std::vector<int> data_type;

  data_type a;			// coefficants
  data_type h;			// numerators
  data_type k;			// denominators

  void init()
  {
    h.push_back(0);
    h.push_back(1);

    k.push_back(1);
    k.push_back(0);
  }
};


void test(ContinuedFraction & cf)
{
  cf.computeAll();
  cf.showConvergents();
  cf.showSeries();
}

void type1(int argc, char ** argv)
{
  double n = atof(argv[1]);
  int    i = atoi(argv[2]);

  ContinuedFraction cf(n, i);
  test(cf);
}

void type2(int argc, char ** argv)
{
  std::vector<int> data;

  while ( --argc > 0 ) {
    char const * pch = *++argv;
    data.push_back(atoi(pch));
  }
  
  ContinuedFraction cf(data.begin(), data.end());
  test(cf);
}


int main(int argc, char ** argv)
{

  if ( argc == 3 ) {
    type1(argc, argv);
  }
  else {
    type2(argc, argv);
  }

  return 0;
}
