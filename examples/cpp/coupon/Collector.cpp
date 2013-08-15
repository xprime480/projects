
#include <numeric>
#include <functional>
#include <limits>
#include <iostream>

#include "Collector.h"

Collector::Collector()
  : min_val(std::numeric_limits< DataType >::max() )
  , max_val(std::numeric_limits< DataType >::min() )
{
}

void Collector::add(DataType val)
{
  data.push_back(val);
  if ( val > max_val ) {
    max_val = val;
  }
  if ( val < min_val ) {
    min_val = val;
  }
}

int Collector::count() const
{
  return data.size();
}

Collector::DataType Collector::min() const
{
  return min_val;
}

Collector::DataType Collector::max() const
{
  return max_val;
}

Collector::DataType Collector::sum() const
{
  return std::accumulate(data.begin(), 
			 data.end(), 
			 0.0,  
			 std::plus< DataType >());
}


double Collector::avg() const
{
  if ( count() == 0 ) {
    return (double) min();
  }

  return ( (double) sum() / (double) count() );
}

double Collector::var() const
{
  if ( count() == 0 ) {
    return (double) min();
  }
  
  double mean = avg();

  double val = 0;
  for ( std::vector< DataType >::const_iterator iter = data.begin() ;
	iter != data.end() ;
	++iter ) {
    double t = (double) *iter - mean;
    val += t * t;
  }

  return val / (double) count();
}


void Collector::report() const
{
  std::cout << "count = " << count() << std::endl;
  std::cout << "min = "   << min()   << std::endl;
  std::cout << "max = "   << max()   << std::endl;
  std::cout << "sum = "   << sum()   << std::endl;
  std::cout << "avg = "   << avg()   << std::endl;
  std::cout << "var = "   << var()   << std::endl;
}

