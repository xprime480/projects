
#include <iostream>
#include <string>

#include "timer.h"

#include "duscomputer.h"

using std::cout;
using std::endl;
using std::string;

//Inline function for faster calculation of delta unit sales for three factors
inline double calcDeltaUs3( double base, double * f, int m,  int i, int j )
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
calcDeltaUs4( double base, double * f, int m, int i, int j, int k )
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
calcDeltaUs5( double base, double * f, int m, int i2, int i3, int i4, int i5 )
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

void compute_dus( const double base, 
		  const double * factors, 
		  double * dus, 
		  size_t count )
{
  auto report = [count](const string & interval) { 
    cout << "worked for " << interval << " for input of size " << count << endl;
  };
  auto timer = make_timer(report);

  DusComputer::factor_type _factors(factors, factors + count);
  DusComputer computer(base, _factors);
  computer.compute();
  const DusComputer::dus_type & _dus = computer.results();

  double product = base;
  for ( auto _f : _factors ) {
    product *= _f;
  }
  double sum = base;
  for ( auto _d : _dus ) {
    sum += _d;
  }
  
  cout << endl;
  cout << "sum = " << sum << "; prod = " << product << endl;
  
  for ( size_t i = 0 ; i < count ; ++i ) {
    dus[i] = _dus[i];
    cout << dus[i] << " ";
  }
  cout << endl;;
}

void dustest(int argc, char ** argv)
{
  constexpr const size_t num_factors = 10;

  double factors[num_factors] = { 2.0, 1.0 / 3.0, 4.0, 5.0, 0.15, 2.5, 3.5, 4.5, 0.1, 0.2 };
  double dus[num_factors];
  double base = { 1000.0 };

  cout << calcDeltaUs4( base, factors, 0, 1, 2, 3) << endl;
  cout << calcDeltaUs3( base, factors, 0, 1, 2 ) << endl;

  for ( size_t c = 0 ; c <= num_factors ; ++c ) {
    compute_dus( base, factors, dus, c );
  }
}
