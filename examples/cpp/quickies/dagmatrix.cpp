

/**
 * This code is intended to compute the number of acyclic digraphs
 * with N nodes, but it is wrong.  It fails for case N=5 and above.
 *
 * Don't yet know why.
 *
 */

#include <iostream>
#include <set>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include <vector>

template < int N >
class Matrix
{
public:
  int const size;

  Matrix()
    : size(N)
  {
    for ( int row = 0 ; row < N ; ++row ) {
      for ( int col = 0 ; col < N ; ++col ) {
	clear(row, col);
      }
    }
  }

  int const & get(int row, int col) const
  {
    return data[row][col];
  }

  void set(int row, int col)
  {
    data[row][col] = 1;
  }

  void clear(int row, int col)
  {
    data[row][col] = 0;
  }

protected:
private:
  int data[N][N];
};

template < typename IO, int N >
IO & operator<< (IO & io, Matrix<N> const & m)
{
  for ( int row = 0 ; row < N ; ++row ) {
    for ( int col = 0 ; col < N ; ++col ) {
      io << m.get(row, col) << " ";
    }
    io << "\n";
  }

  return io;
}

template < int N >
bool operator<(Matrix<N> const & x, Matrix<N> const & y) 
{
  for ( int row = 0 ; row < N ; ++row ) {
    for ( int col = 0 ; col < N ; ++col ) {
      int const & xval = x.get(row, col);
      int const & yval = y.get(row, col);
      if ( xval < yval ) {
	return true;
      }
      if ( yval < xval ) {
	return false;
      }
    }
  }

  return false;
}

struct Facts 
{
  std::set<int> upLinks;
  std::set<int> dnLinks;
  std::set<int> upStream;
  std::set<int> dnStream;

  Facts()
  {
  }
};
    
template < int N >
class Usage
{
public:
  int const size;

  Usage(Matrix<N> const & m)
    : size(N)
  {
    for ( int node = 0 ; node < N ; ++node ) {
      groups[node].insert(node);
    }

    for ( int row = 0 ; row < N ; ++row ) {
      for ( int col = row+1 ; col < N ; ++col ) {
	int const link = m.get(row, col);
	if ( link == 1 ) {
	  facts[row].dnLinks.insert(col);
	  facts[col].upLinks.insert(row);

	  std::set<int> tmp;
	  std::set_union(groups[row].begin(), groups[row].end(),
			 groups[col].begin(), groups[col].end(),
			 std::inserter(tmp, tmp.begin()));

	  std::set<int>::const_iterator iter;
	  for ( iter = tmp.begin() ; iter != tmp.end() ; ++iter ) {
	    groups[*iter] = tmp;
	  }
	}
      }
    }

    std::map<int, std::set<int> >::const_iterator iter;
    for ( iter = groups.begin() ; iter != groups.end() ; ++iter ) {
      comps.insert(iter->second);
    }

    for ( int node = 0 ; node < N ; ++node ) {
      Facts & f = facts[node];

      processLinks(f.upLinks, f.upStream, &Facts::upLinks);
      processLinks(f.dnLinks, f.dnStream, &Facts::dnLinks);
    }

    stepX();
  }

  template < typename IO >
  IO & display(IO & io) const
  {
    for ( int i = 0 ; i < N ; ++i ) {
      Facts const & f = facts[i];
      io << *groups.find(i)->second.begin() << ": ";
      io << f.upLinks.size()  << ","
	 << f.dnLinks.size()  << ","
	 << f.upStream.size() << ","
	 << f.dnStream.size() << std::endl;
    }

    std::set<std::set<int> >::const_iterator iter1;
    std::set<int>::const_iterator            iter2;
    for ( iter1 = comps.begin() ; iter1 != comps.end() ; ++iter1 ) {
      std::set<int> const & c = *iter1;
      for ( iter2 = c.begin() ; iter2 != c.end() ; ++iter2 ) {
	io << *iter2 << ",";
      }
      io << ";  ";
    }
    io << std::endl;

    std::multiset<std::list<int> >::const_iterator iter;
    std::ostream_iterator<int> ostr (io, ", ");
    for ( iter = groupCodes.begin() ; iter != groupCodes.end() ; ++iter ) {
      std::copy(iter->begin(), iter->end(), ostr);
      io << std::endl;
    }

    return io;
  }

  std::multiset<std::list<int> > const & getCodes() const
  {
    return groupCodes;
  }

protected:

private:
  Facts facts[N];
  std::map<int, std::set<int> > groups;
  std::set<std::set<int> >      comps;
  std::map<int, int>            isoMap;
  std::multiset<std::list<int> >groupCodes;

  void processLinks(std::set<int> const & init, 
		    std::set<int>       & dst,
		    std::set<int> Facts::* next)
  {
    typedef std::set<int>     d_type;
    typedef std::list<d_type> q_type;
    typedef d_type::iterator  d_iter;

    q_type q;
    q.push_back(init);

    while ( ! q.empty() ) {
      d_type data = q.front();
      q.pop_front();

      for ( d_iter d = data.begin() ; d != data.end() ; ++d ) {
	int n = *d;
	dst.insert(n);
	q.push_back(facts[n].*next);
      }
    }
  }

  void stepX()
  {
    std::map<int, std::set<int> >::const_iterator iter;

    for ( iter = groups.begin() ; iter != groups.end() ; ++iter ) {
      std::list<int> groupCode;
      std::set<int> const & group = iter->second;

      groupCode.push_back(-1 * group.size());

      std::set<int>::const_iterator iter2;
      std::set<std::vector<int> > nodeCodes;
      for ( iter2 = group.begin() ; iter2 != group.end() ; ++iter2 ) {
	std::vector<int> nodeCode(5);
	int node = *iter2;
	Facts & f = facts[node];

	nodeCode[0] = f.upLinks.size();
	nodeCode[1] = -1 * f.dnLinks.size();
	nodeCode[2] = f.upStream.size();
	nodeCode[3] = -1 * f.dnStream.size();
	nodeCode[4] = node;

	nodeCodes.insert(nodeCode);
      }

      int n = N;
      std::set<std::vector<int> >::const_iterator iter3;
      std::list<int> nodes;
      for ( iter3 = nodeCodes.begin() ; iter3 != nodeCodes.end() ; ++iter3 ) {
	std::vector<int> const & nodeCode = *iter3;
	for ( int i = 0 ; i < 4 ; ++i ) {
	  groupCode.push_back(nodeCode[i]);
	}
	int nn = nodeCode[4];
	n = std::min(n, nn);
	// nodes.push_back(nn);
      }
      // groupCode.push_back(n);
      // std::copy(nodes.begin(), nodes.end(), std::back_inserter(groupCode));
      groupCodes.insert(groupCode);
    }
  }
};

template < typename IO, int N >
IO & operator<< (IO & io, Usage<N> const & u)
{
  u.display(io);
  return io;
}

template<int N>
void populate(std::set<Matrix<N> > & matrices)
{
  std::set<std::multiset<std::list<int> > > canon;

  int const bits = N * (N-1) / 2;
  unsigned long max = 1 << bits;

  for ( unsigned int i = 0 ; i < max ; ++i ) {
    int j = i;
    Matrix<N> m;
    for ( int row = 0 ; row < N && j != 0; ++row ) {
      for ( int col = row+1 ; col < N && j != 0 ; ++col ) {
	int bit = j % 2;
	j >>= 1;
	if ( bit == 1 ) {
	  m.set(row, col);
	}
      }
    }

    // std::cerr << i << ":" << std::endl;
    // std::cerr << m << std::endl;
    matrices.insert(m);

    Usage<N> u(m);
    // std::cerr << u << std::endl;
    canon.insert(u.getCodes());
  }

  std::cerr << canon.size() << " canonical forms" << std::endl;
}

template < int N >
void test()
{
  Matrix<N> m;
  std::cout << m.size << std::endl;

  std::set<Matrix<N> > matrices;
  populate(matrices);
  std::cout << matrices.size() << " raw forms" << std::endl;
}

int main(int argc, char ** argv)
{
  test<0>();
  test<1>();
  test<2>();
  test<3>();
  test<4>();
  test<5>();

  return 0;
}
