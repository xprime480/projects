
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <numeric>

using namespace std;

class LazySeq
{
public:
  virtual ~LazySeq()
  {
  }

  virtual bool hasMore()
  {
    if ( buffer.empty() ) {
      step();
    }
    return ! buffer.empty();
  }

  virtual int next() 
  {
    if ( ! hasMore() ) {
      throw runtime_error("Called next on an empty sequence");
    }

    int v = buffer.front();
    buffer.pop();
    return v;
  }

protected:
  queue<int, list<int> > buffer;

  static size_t const lookahead;

  virtual void step()
  {
  }

private:
};

size_t const LazySeq::lookahead = 20;


class LazySeqUtils
{
public:
  static size_t count(LazySeq & seq)
  {
    size_t n = 0;
    while ( seq.hasMore() ) {
      ++n;
      seq.next();
    }
    return n;
  }

  static void print(LazySeq & seq)
  {
    while ( seq.hasMore() ) {
      cout << seq.next() << " ";
    }
    cout << endl;
  }

  static pair<int, int> minmax(LazySeq & seq)
  {
    int minv = -1;
    int maxv = -1;
    if ( seq.hasMore() ) {
      minv = maxv = seq.next();
    }

    while ( seq.hasMore() ) {
      int v = seq.next();
      minv = min(minv, v);
      maxv = max(maxv, v);
    }

    return make_pair(minv, maxv);
  }

  static LazySeq * take(LazySeq & seq, size_t count);
  static LazySeq * drop(LazySeq & seq, size_t count);
};

class AnonSeqBase : public LazySeq
{
public:
  AnonSeqBase()
  {
    buffer.push(1);
    buffer.push(1);
  }

  ~AnonSeqBase()
  {
  }

private:
  virtual void step()
  {
  }
};


class AnonSeq : public LazySeq
{
public:
  AnonSeq(LazySeq & src)
    : source(src)
    , pending(-1)
  {
  }
  
  void step()
  {
    for ( size_t i = 0 ; i < (lookahead / 2) ; ++i ) {
      if ( ! source.hasMore() && pending <= 0 ) {
	return;
      }

      int count = 1;
      int value;

      if ( pending > 0 ) {
	value = pending;
	pending = -1;
      }
      else {
	value = source.next();
      }

      while ( source.hasMore() ) {
	int nv = source.next();
	if ( nv != value ) {
	  pending = nv;
	  break;
	}
	++count;
      }

      buffer.push(count);
      buffer.push(value);
    }
  }

private:
  LazySeq & source;
  int pending;
};

class Taker : public LazySeq
{
public:
  Taker(LazySeq & src, size_t n)
    : source(src)
    , max(n)
    , taken(0)
  {
  }

  void step()
  {
    for ( size_t i = 0 ; i < lookahead ; ++i ) {
      if ( taken >= max ) {
	return;
      }
      if ( ! source.hasMore() ) {
	return;
      }

      buffer.push(source.next());
      ++taken;
    }
  }

private:
  LazySeq & source;
  size_t max;
  size_t taken;
};

class Dropper : public LazySeq
{
public:
  Dropper(LazySeq & src, size_t n)
    : source(src)
    , dropped(false)
    , max(n)
  {
  }

  void step()
  {
    if ( ! dropped ) {
      dropped = true;
      for ( size_t i = 0 ; i < max ; ++i ) {
	if ( ! source.hasMore() ) {
	  return;
	}
	source.next();
      }
    }

    for ( size_t i = 0 ; i < lookahead ; ++i ) {
      if ( ! source.hasMore() ) {
	return;
      }
      buffer.push(source.next());
    }
  }

private:
  LazySeq & source;
  bool dropped;
  size_t max;
};

class Fibonacci : public LazySeq
{
public:
  Fibonacci()
    : a(1)
    , b(1)
  {
  }

protected:
  virtual void step()
  {
    for ( size_t i = 0 ; i < lookahead ; ++i ) {
      int rv = a;
      int nv = a+b;
      a = b;
      b = nv;
      buffer.push(rv);
    }
  }

private:
  int a, b;
};

LazySeq * LazySeqUtils::take(LazySeq & seq, size_t count)
{
  return new Taker(seq, count);
}

LazySeq * LazySeqUtils::drop(LazySeq & seq, size_t count)
{
  return new Dropper(seq, count);
}

void test(size_t depth)
{
  if ( depth == 0 ) {
    return;
  }

  LazySeq * seq = new AnonSeqBase;
  for ( size_t i = 1 ; i < depth ; ++i ) {
    LazySeq * temp = new AnonSeq(*seq);
    seq = temp;
  }

  // cout << "Length is " << LazySeqUtils::count(*seq) << endl;
  pair<int, int> minmax = LazySeqUtils::minmax(*seq);
  cout << "Extremes: " << minmax.first << ", " << minmax.second << endl;
}

class Naturals : public LazySeq
{
public:
  Naturals()
    : n(1)
  {
  }

  virtual bool hasMore()
  {
    return n >= 0;
  }

  virtual int next() 
  {
    if ( ! hasMore() ) {
      throw runtime_error("Called next on an empty sequence");
    }
    return n++;
  }

protected:

private:
  int n;
};

class GeneralizedHamming : public LazySeq
{
public:
  GeneralizedHamming(set<int> const & g)
    : basegen(g)
  {
    gen.insert(g.begin(), g.end());
  }

protected:
  virtual void step()
  {
    for ( size_t i = 0 ; i < lookahead ; ++i ) {
      if ( gen.empty() ) {
	return;
      }
    
      set<int>::iterator iter = gen.begin();
      int v = *iter;
      gen.erase(iter);

      buffer.push(v);

      for ( iter = basegen.begin() ; iter != basegen.end() ; ++iter ) {
	int newv = v * *iter;
	if ( newv > 0 ) {
	  gen.insert(newv);
	}
	else {
	  break;
	}
      }
    }
  }

private:
  set<int> gen;
  set<int> basegen;
};

class Hamming : public GeneralizedHamming
{
public:
  Hamming()
    : GeneralizedHamming(getGenerators())
  {
  }

protected:

private:
  static set<int> & getGenerators()
  {
    static set<int> g;

    static bool done = false;
    if ( ! done ) {
      g.insert(2);
      g.insert(3);
      g.insert(5);
      done = true;
    }

    return g;
  }
};

int timetest()
{
  size_t const N = 100000000;

  LazySeq * y = new Naturals();
  LazySeq * z = LazySeqUtils::take(*y, N);
  LazySeq * w = LazySeqUtils::drop(*z, N/2);
  cout << "Count = " << LazySeqUtils::count(*w) << endl;
  delete w;
  delete z;
  delete y;
  return 0;
}

int hammingtest()
{
  size_t const N = 30;

  {
    LazySeq * y = new Hamming();
    LazySeq * z = LazySeqUtils::take(*y, N);
    LazySeqUtils::print(*z);
    delete z;
    delete y;
  }

  {
    set<int> g;
    g.insert(3);
    g.insert(7);
    g.insert(11);
    LazySeq * y = new GeneralizedHamming(g);
    LazySeq * z = LazySeqUtils::take(*y, N);
    LazySeqUtils::print(*z);
    delete z;
    delete y;
  }

  return 0;
}

int main(int argc, char ** argv)
{
  // timetest(); return 0;

  hammingtest(); return 0;


  AnonSeqBase s;
  AnonSeq     t(s);
  LazySeqUtils::print(t);

  for ( size_t i = 1 ; i <= 50 ; ++i ) {
    // test(i);			// 
  }

  Fibonacci f;
  LazySeqUtils::print(*LazySeqUtils::take(f, 20));

  return 0;
}
