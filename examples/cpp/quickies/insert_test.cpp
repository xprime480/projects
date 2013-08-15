
#include <set>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
  set<int>  si;
  size_t count(0);

  for ( size_t i = 0 ; i < 100 ; ++i ) {
    if ( si.insert(123).second ) {
      ++count;
    }
  }

  cout << count << endl;
}
