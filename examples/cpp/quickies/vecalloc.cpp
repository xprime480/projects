#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
  vector<int> vi;
  vi.reserve(12);
  cout << vi.capacity() << endl;

  vi.push_back(5);
  cout << vi.size() << endl;

  for ( int i = 0 ; i < 25 ; ++i ) {
    vi.push_back(i);
  }
  cout << vi.size() << endl;
  cout << vi.capacity() << endl;
  
  return 0;
}
