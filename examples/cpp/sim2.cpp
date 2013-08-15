
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <time.h>
#include <algorithm>
#include <random>

using namespace std;

typedef vector<int> DataType;

DataType makeRandomVector(size_t size)
{
  DataType data;
  for ( int i = 0 ; i < size ; ++i ) {
    data.push_back(rand() % 100);
  }
  return data;
}

void displayData(DataType const & data)
{
  copy(data.begin(), data.end(), 
       ostream_iterator<DataType::value_type>(cout, " "));
  cout << endl;
}

class Trial
{
public:
  Trial()
    : winners(0)
    , losers(0)
    , ties(0)
  {
  }

  virtual ~Trial() 
  {
  }

  virtual void run(DataType const & data1, DataType const & data2) = 0;

  size_t getWinners() const
  {
    return winners;
  }

protected:
  size_t winners;
  size_t losers;
  size_t ties;

private:
};

class InOrderTrial : public Trial
{
public:
  virtual void run(DataType const & data1, DataType const & data2)
  {
    size_t n = data1.size();
    for ( size_t i = 0 ; i < n ; ++i ) {
      int diff = data1[i] - data2[i];
      if ( diff > 0 ) {
	++winners;
      }
      else if ( diff < 0 ) {
        ++losers;
      }
      else {
	ties++;
      }
    }
  }
};

class PerfectInfoTrial : public Trial
{
public:
  virtual void run(DataType const & data1, DataType const & data2)
  {
    DataType d1(data1);
    DataType d2(data2);
    sort(d1.rbegin(), d1.rend());
    sort(d2.rbegin(), d2.rend());
#if 0
    displayData(d1);
    displayData(d2);
    cout << "--------------------------------------" << endl;
#endif

    size_t n = data1.size();
    for ( size_t i = 0 ; i < n ; ++i ) {
      int i1 = d1[i];
      int i2 = -1;
      for ( size_t j = 0 ; j < n ; ++j ) {
	if ( d2[j] > 0 && d2[j] < i1 ) {
	  i2 = d2[j];
	  d2[j] = -1;
	  break;
	}
      }
      if ( i2 < 0 ) {
	for ( size_t j = 0 ; j < n ; ++j ) {
	  if ( d2[j] > 0 ) {
	    i2 = d2[j];
	    d2[j] = -1;
	    break;
	  }
	}
      }

      int diff = i1 - i2;
      if ( diff > 0 ) {
	++winners;
      }
      else if ( diff < 0 ) {
        ++losers;
      }
      else {
	ties++;
      }
    }
  }
};

template<typename T>
class TrialManager
{
public:
  TrialManager(size_t N)
    : trials(new T[N])
    , count(N)
  {
  }
  
  ~TrialManager()
  {
    delete[] trials;
  }

  void run(size_t dataSize = 100)
  {
    for ( size_t i = 0 ; i < count ; ++i ) {
      DataType data1(makeRandomVector(dataSize));
      DataType data2(makeRandomVector(dataSize));

      trials[i].run(data1, data2);
    }
    
    vector<int> results(dataSize + 1);
    int sum;
    for ( size_t i = 0 ; i < count ; ++i ) {
      int value = trials[i].getWinners();
      sum += value;
      results[value]++;
    }

    for ( size_t i = 0 ; i < dataSize+1 ; ++i ) {
      // cout << i << " " << results[i] << endl;
    }

    cout << "Average number of wins: " << ((double) sum / count)
	 << " out of " << dataSize
	 << "; " << count << " passes"
	 << endl;
  }

protected:
private:
  T * trials;
  size_t count;
};

void test()
{
  TrialManager<InOrderTrial> inOrderManager(10000);
  inOrderManager.run();

  TrialManager<PerfectInfoTrial> perfectInfoManager(10000);
  perfectInfoManager.run();
}

int main(int argc, char ** argv)
{
  srand(time(0));
  test();
  return 0;
}
