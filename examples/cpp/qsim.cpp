
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

class Q
{
public:
  Q()
  {
  }

  void init(size_t count)
  {
    q.clear();
    for ( size_t i = 0 ; i < count ; ++i ) {
      q.push_back(i);
    }
  }

  void run(size_t runsize, size_t listsize, size_t repeat)
  {
    if ( runsize > listsize ) {
      cerr << "runsize is bigger than listsize" << endl;
      return;
    }
    if ( listsize > q.size() ) {
      cerr << "listsize is bigger than q.size" << endl;
      return;
    }

    for ( size_t i = 0 ; i < repeat ; ++i ) {
      permute(runsize, listsize);
    }
  }

  void report()
  {
    vector<size_t>::const_iterator from = q.begin();

    while ( from < q.end() ) {
      vector<size_t>::const_iterator to = from;
      advance(to, 20);
      while ( from < to && from < q.end() ) {
	cout << *from << " ";
	++from;
      }
      cout << endl;
    }
  }

private:
  vector<size_t> q;
  
  void permute(size_t runsize, size_t listsize) 
  {
    set<size_t> indices;
    while ( indices.size() < runsize ) {
      indices.insert(rand() % listsize);
    }

    vector<size_t> elements;
    set<size_t>::const_reverse_iterator i;
    for ( i = indices.rbegin() ; i != indices.rend() ; ++i ) {
      vector<size_t>::iterator j = q.begin() + *i;
      elements.push_back(*j);
      q.erase(j);
    }

    random_shuffle(elements.begin(), elements.end());
    vector<size_t>::const_iterator k;
    for ( k = elements.begin() ; k != elements.end() ; ++k ) {
      q.push_back(*k);
    }
  }

};

int main(int argc, char ** argv)
{
  srand(time(0));

  if ( 0 ) {
    Q q;
    q.init(500);
    q.run(5, 10, 1000000);
    q.report();
  }

  Q e;
  e.init(10);
  cout << "============================" << endl;
  e.report();
  for ( int i = 0 ; i < 100 ; ++i ) {
    cout << "============================" << endl;
    e.run(1, 2, 1);
    e.report();
  }

  return 0;
}
