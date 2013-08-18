
#include <set>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <numeric>
#include <algorithm>

int const N_W   = 5;
int const MAX_W = 59;
int const MAX_R = 35;
int const SUM   = 153;

int main(int, char **)
{
  srand(time(0));
  while ( true ) {
    std::set<int> nums;
    while ( nums.size() < N_W ) {
      nums.insert(1 + rand() % MAX_W);
    }
    int sum = std::accumulate( nums.begin(), nums.end(), 0, std::plus<int>() );
    if ( sum != SUM ) {
      continue;
    } 

    std::copy( nums.begin(), nums.end(), 
	       std::ostream_iterator<int>( std::cout, "  " ) );
    break;
  }

  std::cout << " / " << (1 + rand() % MAX_R) << "\n";
}
