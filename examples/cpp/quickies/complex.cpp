#include <complex>
#include <iostream>

int main(int, char**)
{
  std::complex<double> zero(0,0);
  std::complex<double> two(2,0);
  std::complex<double> i(0,1);
  
  std::cerr << std::pow(zero,zero) << "\n";
  std::cerr << std::pow(two,zero) << "\n";
  std::cerr << std::pow(two,two) << "\n";
  std::cerr << std::pow(i,i) << "\n";
  std::cerr << std::pow(i,two) << "\n";
  return 0;
}
