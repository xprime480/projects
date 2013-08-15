
#include <iostream>
#include <list>
#include <queue>
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

  virtual bool hasMore() = 0;
  virtual int next() = 0;
};

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
};

class AnonSeqBase : public LazySeq
{
public:
  AnonSeqBase()
  {
    seq.push(1);
    seq.push(1);
  }

  ~AnonSeqBase()
  {
  }

  virtual bool hasMore()
  {
    return ! seq.empty();
  }

  virtual int next()
  {
    if ( ! hasMore() ) {
      throw runtime_error("Called next on an empty sequence");
    }

    int v = seq.front();
    seq.pop();
    return v;
  }

private:
  queue<int, list<int> > seq;
};


class AnonSeq : public LazySeq
{
public:
  AnonSeq(LazySeq & src)
    : source(src)
    , pending(-1)
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
  

  void step()
  {
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

private:
  queue<int, list<int> > buffer;
  LazySeq & source;
  int pending;
};

class Taker : public LazySeq
{
public:
  Taker(LazySeq & src, size_t n)
    : source(src)
    , taken(0)
    , max(n)
  {
  }

  virtual bool hasMore()
  {
    if ( taken >= max ) {
      return false;
    }
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
    ++taken;
    return v;
  }
  

  void step()
  {
    if ( ! buffer.empty() ) {
      return;
    }
    if ( ! source.hasMore() ) {
      return;
    }

    buffer.push(source.next());
  }

private:
  queue<int, list<int> > buffer;
  LazySeq & source;
  size_t max;
  size_t taken;
};

class Fibonacci : public LazySeq
{
public:
  Fibonacci()
    : a(1)
    , b(1)
  {
  }

  virtual bool hasMore()
  {
    return true;
  }

  virtual int next()
  {
    int rv = a;
    int nv = a+b;
    a = b;
    b = nv;
    return rv;
  }

private:
  int a, b;
};

LazySeq * LazySeqUtils::take(LazySeq & seq, size_t count)
{
  return new Taker(seq, count);
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
    return n > 0;
  }

  virtual int next()
  {
    if ( ! hasMore() ) {
      throw runtime_error("Called next on an empty sequence");
    }
    return n++;
  }

private:
  int n;
};

int timetest()
{
  LazySeq * y = new Naturals();
  LazySeq * z = LazySeqUtils::take(*y, 100000000);
  cout << "Count = " << LazySeqUtils::count(*z) << endl;
  delete z;
  delete y;
}

int main(int argc, char ** argv)
{
  timetest();
  return 0;


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
