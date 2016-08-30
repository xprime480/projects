
#include <iostream>
#include <string>
#include <numeric>

#include "timer.h"

#include "duscomputer.h"

using std::cout;
using std::endl;
using std::string;

//Inline function for faster calculation of delta unit sales for three factors
inline double calcDeltaUs3( const double & base, const double * f, int m,  int i, int j )
{
  if( f[m] != 1.0) {
    return base*(f[m]-1.0)*(2.0*(1+f[i]*f[j])+f[i]+f[j])/6.0;
  }
  else {
    return 0.0;
  }
}

//Inline function for faster calculation of delta unit sales for four factors
inline double 
calcDeltaUs4( const double & base, const double * f, int m, int i, int j, int k )
{
  if ( f[m] != 1.0) {
    return base*(f[m]-1.0)*
      (3.0*(1+f[i]*f[j]*f[k])+f[i]+f[j]+f[k]+f[i]*f[j]+f[j]*f[k]+f[i]*f[k])/12.0;
  }
  else {
    return 0.0;
  }
}

//Inline function for faster calculation of delta unit sales for five factors
inline double 
calcDeltaUs5( const double & base, const double * f, int m, int i2, int i3, int i4, int i5 )
{
  if( f[m] != 1.0) {
    return base*(f[m]-1.0)*
      (
       24.0*(1+f[i2]*f[i3]*f[i4]*f[i5])+
       6.0*(f[i2]+f[i3]+f[i4]+f[i5] +
	    f[i2]*f[i3]*f[i4] + f[i2]*f[i3]*f[i5] + f[i2]*f[i4]*f[i5] +
	    f[i3]*f[i4]*f[i5]) +
       4.0*(f[i2]*f[i3]+f[i2]*f[i4]+f[i3]*f[i4]+f[i3]*f[i5]+f[i4]*f[i5])
       )/120.0;
  } 
  else {
    return 0.0;
  }
}

class DusComputerTester
{
public:
  DusComputerTester(
      const double _base,
      const double * _factors,
      size_t _count
  )
: base(_base)
, factors(_factors, _factors + _count)
, count(_count)
, computer(_base, factors)
, dus(nullptr)
, duration(0)
{
}

 void execute()
 {
   Timer t;
   t.start();
   computer.compute();
   dus = &computer.results();
   t.stop();
   duration = t.duration();
 }
//
 template <typename OS>
 OS & report(OS & os)
 {
   os << endl;
   os << "worked for " << duration.count() << " seconds for input of size " << count << '\n';

   using std::accumulate;
   const double product = accumulate(factors.begin(), factors.end(), base, [](double a, double b){return a*b;});
   const double sum = accumulate(dus->begin(), dus->end(), base, [](double a, double b){return a+b;});
   os << "sum = " << sum << "; product = " << product << '\n';

   for ( size_t i = 0 ; i < count ; ++i ) {
       os << (*dus)[i] << " ";
   }
   os << '\n';
   return os;
}

private:
  const double base;
  DusComputer::factor_type factors;
  size_t count;
  DusComputer computer;
  const DusComputer::dus_type * dus;
  Timer::dur duration;
};

void dustest(int argc, char ** argv)
{
  constexpr const size_t num_factors = 10;

  const double factors[num_factors] = { 2.0, 1.0 / 3.0, 4.0, 5.0, 0.15, 2.5, 3.5, 4.5, 0.1, 0.2 };
  const double base = { 1000.0 };

  cout << calcDeltaUs4( base, factors, 0, 1, 2, 3) << endl;
  cout << calcDeltaUs3( base, factors, 0, 1, 2 ) << endl;

  for ( size_t c = 0 ; c <= num_factors ; ++c ) {
      DusComputerTester tester(base, &factors[0], c);
      tester.execute();
      tester.report(cout);
  }
}
