
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class AnonSeq
{
public:
  AnonSeq()
    : max(-1)
  {
    seq.push_back(1);
    seq.push_back(1);
  }

  void step()
  {
    vector<int> temp;
    temp.swap(seq);
    temp.push_back(-1);		// sentinal value

    vector<int>::const_iterator iter = temp.begin();
    int value = *iter;
    while ( iter != temp.end() ) {
      if ( value > max ) {
	max = value;
	cout << "New max: " << max << endl;
      }
      int hold = value;
      if ( hold < 0 ) {
	break;
      }

      int count = 1;
      for ( ;; ) {
	value = *++iter;
	if ( value != hold ) {
	  break;
	}
	++count;
      } 

      seq.push_back(count);
      seq.push_back(hold);
    }
  }

  void report()
  {
    cout << "Length = " << seq.size() << endl;
    return;
    copy(seq.begin(), seq.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }

private:
  vector<int> seq;
  int max;
};

int main(int argc, char ** argv)
{
  AnonSeq s;
  for ( int i = 0 ; i < 50 ; ++i ) {
    s.step();
  }
  s.report();


  return 0;
}
