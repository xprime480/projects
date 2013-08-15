
// from http://www.cplusplus.com/reference/stl/multimap/find/

// multimap::find
#include <iostream>
#include <map>
using namespace std;

int main ()
{
  multimap<char,int> mymm;
  multimap<char,int>::iterator it;

  mymm.insert (pair<char,int>('x',10));
  mymm.insert (pair<char,int>('y',20));
  mymm.insert (pair<char,int>('z',30));
  mymm.insert (pair<char,int>('z',40));

  it=mymm.find('x');
  mymm.erase (it);
  mymm.erase (mymm.find('z'));

  // print content:
  cout << "elements in mymm:" << endl;
  cout << "y => " << mymm.find('y')->second << endl;
  cout << "z => " << mymm.find('z')->second << endl;

  return 0;
}
