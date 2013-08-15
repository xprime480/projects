

#include <functional>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <iostream>
#include <iterator>

using namespace std;

typedef set<int> cont_t;
typedef cont_t::const_iterator iter_t;

struct Triple
{
  Triple()
    : a(0)
    , b(0)
    , c(0) 
  {
  }

  Triple(int _a, int _b, int _c)
    : a(_a)
    , b(_b)
    , c(_c) 
  {
  }

  void print() const
  {
    cout << a << "." << b << "." << c << endl;
  }

  int a;
  int b;
  int c;
};

class TripleIterator : public iterator<forward_iterator_tag, Triple>
{
public:
  TripleIterator(iter_t _ai,
		 iter_t _bi,
		 iter_t _ci,
		 class Triples const * _triples)
    : ai(_ai)
    , bi(_bi)
    , ci(_ci)
    , triples(_triples)
    , t(0,0,0)
  {
  }

  TripleIterator(TripleIterator const & that)
    : ai(that.ai)
    , bi(that.bi)
    , ci(that.ci)
    , triples(that.triples)
    , t(that.t)
  {
  }

  TripleIterator & operator=(TripleIterator const & that) 
  {
    ai = that.ai;
    bi = that.bi;
    ci = that.ci;
    triples = that.triples;
    t = that.t;
    return *this;
  }

  TripleIterator operator++();

  TripleIterator operator++(int)
  {
    TripleIterator tmp(*this);
    operator++();
    return tmp;
  }

  bool operator==(TripleIterator const & that)
  {
    return ai == that.ai && bi == that.bi && ci == that.ci;
  }

  bool operator!=(TripleIterator const & that) 
  {
    return ! this->operator==(that);
  }

  Triple & operator*()
  {
    t.a = *ai;
    t.b = *bi;
    t.c = *ci;
    return t;
  }

private:
  iter_t ai;
  iter_t bi;
  iter_t ci;
  Triples const * triples;

  Triple t;
    
};

class Triples
{
public:
  friend class TripleIterator;

  Triples(cont_t const & _as,
	  cont_t const & _bs,
	  cont_t const & _cs)
    : as(_as)
    , bs(_bs)
    , cs(_cs)
  {
  }

  TripleIterator begin()
  {
    return TripleIterator(as.begin(), bs.begin(), cs.begin(), this);
  }

  TripleIterator end()
  {
    return TripleIterator(as.end(), bs.end(), cs.end(), this);
  }

private:
  cont_t const & as;
  cont_t const & bs;
  cont_t const & cs;
};

TripleIterator TripleIterator::operator++()
{
  ++ci;
  if ( ci == triples->cs.end() ) {
    ci = triples->cs.begin();

    ++bi;
    if ( bi == triples->bs.end() ) {
      bi = triples->bs.begin();

      ++ai;
      if ( ai == triples->as.end() ) {
	bi = triples->bs.end();
	ci = triples->cs.end();
      }
    }
  }

  return *this;
}


class Test
{
public:

  void go()
  {
    cont_t a;
    cont_t b;
    cont_t c;

    fill(a);
    fill(b);
    fill(c);

    Triples t(a, b, c);

    for_each(t.begin(), t.end(), mem_fun_ref(&Triple::print));

    triple = Triple();
    //    for_each(t.begin(), t.end(), bind1st(mem_fun(&Test::add), this));
    triple.print();
  }

private:

  Triple triple;

  void add(Triple const & t)
  {
    triple.a += t.a;
    triple.b += t.b;
    triple.c += t.c;
  }

  void fill(cont_t & s) 
  {
    while ( s.size() < 5 ) {
      s.insert(rand() % 10);
    }
  }
};



int main(int,char**)
{
  srand(time(0));

  Test t;
  t.go();

  return 0;
}
