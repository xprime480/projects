#include <stdio.h>
#include <map>
#include <vector>
#include <sys/timeb.h>
#include <stdlib.h>

using namespace std;

// C++ STL map<int, V>
template<typename V> class StlIntHash : public map<int, V>
{
};

// An integer key hash table. It is a vector of map<int, V>. The
// vector is indexed by (key % 127).
//
template<typename V, int Sz=128> class PioIntHash
{
public:

  typedef map<int, V> MapType;

  class iterator
  {
  public:

    iterator()
    {
      m_Map = NULL;
      m_Index = 0;
    }

    iterator(PioIntHash* p_Map, 
	     size_t p_Index, 
	     typename MapType::iterator& p_Iter)
    {
      m_Map = p_Map;
      m_Index = p_Index;
      m_Iter = p_Iter;
    }

    virtual ~iterator()
    {
    }

    iterator(const iterator& p_Value)
    {
      *this = p_Value;
    }

    const iterator& operator=(const iterator& p_Value)
    {
      if ( this != & p_Value )
	{
	  m_Map = p_Value.m_Map;
	  m_Index = p_Value.m_Index;
	  m_Iter = p_Value.m_Iter;
	}
      return(*this);
    }

    bool operator!=(const iterator& p_Value) const
    {
      return(m_Index != p_Value.m_Index || m_Map != p_Value.m_Map || m_Iter != p_Value.m_Iter);
    }

    typename MapType::iterator operator->()
    {
      return(m_Iter);
    }

    iterator& operator++()
    {
      if ( ++m_Iter != m_Map->m_Data[m_Index].end() )
	{
	  return(*this);
	}
	
      for ( ++m_Index; m_Index < m_Map->m_HashTableSize; ++m_Index )
	{
	  if ( !m_Map->m_Data[m_Index].empty() )
	    {
	      m_Iter = m_Map->m_Data[m_Index].begin();
	      return(*this);
	    }
	}

      m_Index = m_Map->m_HashTableBits;
      m_Iter = m_Map->m_Data[m_Map->m_HashTableBits].end();
      return(*this);
    }

  private:

    PioIntHash*                m_Map;
    size_t                     m_Index;
    typename MapType::iterator m_Iter;

    friend class               PioIntHash;
  };

  PioIntHash()
  {	// m_HashTableSize needs to be a power of 2.
    m_HashTableSize = Sz;
    m_HashTableBits = m_HashTableSize - 1;
    for ( size_t i = 0; i < m_HashTableSize; ++i ) {
      m_Data.push_back(MapType());
    }
  }

  void clear()
  {
    for ( size_t i = 0; i < m_HashTableSize; ++i ) {
      m_Data[i].clear();
    }
  }

  size_t size() const
  {
    size_t s = 0;
    for ( size_t i = 0; i < m_HashTableSize; ++i ) {
      s += m_Data[i].size();
    }
    return(s);
  }

  bool empty() const
  {
    for ( size_t i = 0; i < m_HashTableSize; ++i ) {
      if ( !m_Data.empty() ) {
	return(false);
      }
    }

    return(true);
  }

  V& operator[](int p_Key)
  {
    return(m_Data[p_Key & m_HashTableBits][p_Key]);
  }

  iterator find(int p_Key)
  {
    size_t idx = p_Key & m_HashTableBits;
    typename MapType::iterator i = m_Data[idx].find(p_Key);
    if ( i == m_Data[idx].end() ) {
      iterator it(this, m_HashTableBits, i);
      return(it);
    }
    else {
      iterator it(this, idx, i);
      return(it);
    }
  }

  iterator begin()
  {
    for ( size_t Index1 = 0; Index1 < m_HashTableSize; ++Index1 ) {
      if ( !m_Data[Index1].empty() ) {
	typename MapType::iterator i = m_Data[Index1].begin();
	iterator it(this, Index1, i);
	return(it);
      }
    }

    return end();
  }

  iterator end()
  {
    typename MapType::iterator i = m_Data[m_HashTableBits].end();
    iterator it(this, m_HashTableBits, i);
    return(it);
  }

private:

  vector<MapType> m_Data;
  size_t          m_HashTableSize;
  size_t          m_HashTableBits;

  friend class    iterator;
};

class BsTime
{
public:

  BsTime(bool p_StartTimer = false)
  {
    m_BegTimeSec = m_BegTimeMSec = 0;

    if ( p_StartTimer ) {
      Start();
    }
  }

public:

  void Start()
  {
    struct timeb curtime;
    ftime(&curtime);
    m_BegTimeSec = curtime.time;
    m_BegTimeMSec = curtime.millitm;
  }

  unsigned int GetElapseTime() const
  {
    struct timeb curtime;
    ftime(&curtime);
    return (curtime.time - m_BegTimeSec) *1000 + (curtime.millitm - m_BegTimeMSec);
  }

protected:

  unsigned int m_BegTimeSec;
  unsigned int m_BegTimeMSec;
};


template <typename T>
void test(size_t TestSize, char const * p_Name)
{
  T table;
  BsTime timer;
  unsigned long sum;
  size_t Size;

  printf("Test %s ...\n", p_Name);

  timer.Start();
  for ( unsigned int i = 1; i <= TestSize; ++i ) {
    table[i] = i;
  }
  printf("  Time to prepare table:              %7d\n", (int) timer.GetElapseTime());

  sum = 0;
  timer.Start();
  Size = (int) table.size();
  for ( unsigned int i = 1; i <= Size; ++i ) {
    sum += table[i];
  }
  printf("  Time to access table via index:     %7d --- %15lu\n", (int) timer.GetElapseTime(), sum);

  sum = 0;
  timer.Start();
  Size = (int) table.size();
  for ( unsigned int i = 1; i <= Size; ++i ) {
    sum += table.find(i)->second;
  }
  printf("  Time to access table via find:      %7d --- %15lu\n", (int) timer.GetElapseTime(), sum);

  sum = 0;
  timer.Start();
  for ( typename T::iterator i = table.begin(); i != table.end(); ++i ) {
    sum += i->second;
  }
  printf("  Time to access table via iterator:  %7d --- %15lu\n", (int) timer.GetElapseTime(), sum);
}

int main(int argc, char** argv)
{
  unsigned TestSize = 10000;
  if ( argc == 2 ) {
    TestSize = atoi(argv[1]);
    if ( TestSize == 0 ) {
      TestSize = 10000;
    }
  }

  printf("Test size:                            %7d\n", TestSize);
  test<StlIntHash<int> >      (TestSize, "StlIntHash<int>");
  test<PioIntHash<int,  128> >(TestSize, "PioIntHash<int,  128>");
  test<PioIntHash<int, 1024> >(TestSize, "PioIntHash<int, 1024>");
  test<PioIntHash<int, 8192> >(TestSize, "PioIntHash<int, 8192>");

  test<PioIntHash<int, 10000> >(TestSize, "PioIntHash<int, 10000>");

  return 0;
}

