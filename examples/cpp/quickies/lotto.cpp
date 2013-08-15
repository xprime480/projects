
#include <set>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <numeric>
#include <algorithm>

int main(int, char **)
{
  srand(time(0));
  while ( true ) {
    std::set<int> nums;
    while ( nums.size() < 5 ) {
      nums.insert(1 + rand() % 55);
    }
    int sum = std::accumulate( nums.begin(), nums.end(), 0, std::plus<int>() );
    if ( sum != 153 ) {
      continue;
    } 

    std::copy( nums.begin(), nums.end(), 
	       std::ostream_iterator<int>( std::cout, "  " ) );
    break;
  }

  std::cout << " / " << (1 + rand() % 42) << "\n";
}
