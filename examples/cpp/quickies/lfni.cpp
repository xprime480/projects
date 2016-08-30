
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <cmath>
#include <cassert>

/*!
  \brief Iterator through a sequence_adapter
*/
template <typename Container>
struct sequence_adapter_iterator : 
  public std::iterator<std::input_iterator_tag, typename Container::value_type>
{
  typedef          Container                container_type;
  typedef typename Container::value_type    value_type;

  sequence_adapter_iterator(container_type * c) 
    : end(false)
    , container(c)
  {
    assert(container);
    end = ! container->has_next();
  }

  sequence_adapter_iterator() 
    : end(true)
    , container(0)
  {
  }

  value_type operator*()
  {
    value_type t = container->next();
    end = ! container->has_next(); 
    return t;
  }

  sequence_adapter_iterator operator++()
  {
    return *this;
  }

  sequence_adapter_iterator operator++(int)
  {
    return *this;
  }

  bool operator==(sequence_adapter_iterator const & that) const
  {
    if ( end && that.end ) {
      return true;
    }
    if ( end || that.end ) {
      return false;
    }
    return true;
  }

  bool operator!=(sequence_adapter_iterator const & that) const
  {
    return ! (*this == that);
  }

private:
  bool             end;
  container_type * container;
  value_type       value;
};

/*!
  \brief Adapters which take one sequence and return another.
*/
template <typename Iter, 
	  typename Value = typename std::iterator_traits<Iter>::value_type>
struct sequence_adapter
{
  typedef Iter                                            base_iterator;
  typedef Value                                           value_type;
  typedef sequence_adapter<Iter, Value>                   adapter_type;
  typedef sequence_adapter_iterator<adapter_type>         iterator;

  virtual bool has_next() const = 0;
  virtual value_type next() = 0;
};

/*!
  \brief An adapter to return the first N elements of a series.
*/
template <typename Iter>
struct take_adapter : public sequence_adapter<Iter>
{
  typedef sequence_adapter<Iter>             base_type;
  typedef typename base_type::base_iterator  base_iterator;
  typedef typename base_type::value_type     value_type;
  typedef typename base_type::adapter_type   adapter_type;
  typedef typename base_type::iterator       iterator;

  take_adapter(Iter f, Iter t, size_t count) 
    : taken(0)
    , max(count)
    , from(f)
    , to(t)
  {
  }

  iterator begin()
  {
    return iterator(this);
  }
  
  iterator end()
  {
    return iterator();
  }

  virtual bool has_next() const
  {
    if ( from == to ) {
      return false;
    }
    if ( taken >= max ) {
      return false;
    }
    return true;
  }

  virtual value_type next()
  {
    value_type t = *from;
    ++taken;
    ++from;
    return t;
  }

private:
  size_t        taken;
  size_t        max;
  base_iterator from;
  base_iterator to;
};

/*!
  \brief An adapter to return all but the first N elements of a series.
*/
template <typename Iter>
struct drop_adapter : public sequence_adapter<Iter>
{
  typedef sequence_adapter<Iter>             base_type;
  typedef typename base_type::base_iterator  base_iterator;
  typedef typename base_type::value_type     value_type;
  typedef typename base_type::adapter_type   adapter_type;
  typedef typename base_type::iterator       iterator;

  drop_adapter(Iter f, Iter t, size_t count) 
    : from(f)
    , to(t)
  {
    for ( unsigned int i = 0 ; i < count ; ++i ) {
      if ( has_next() ) {
	next();
      }
    }
  }

  iterator begin()
  {
    return iterator(this);
  }
  
  iterator end()
  {
    return iterator();
  }

  virtual bool has_next() const
  {
    return from != to;
  }

  virtual value_type next()
  {
    value_type t = *from;
    ++from;
    return t;
  }

private:
  base_iterator from;
  base_iterator to;
};

/*!
  \brief A generator to create the numbers 1 ... MAX (then wraps)
*/
template <typename Iter>
struct range_generator : public sequence_adapter<Iter>
{
  typedef sequence_adapter<Iter>             base_type;
  typedef typename base_type::base_iterator  base_iterator;
  typedef typename base_type::value_type     value_type;
  typedef typename base_type::adapter_type   adapter_type;
  typedef typename base_type::iterator       iterator;

  range_generator() 
    : current(std::numeric_limits<value_type>::min())
    , final(std::numeric_limits<value_type>::max())
    , step(value_type(1))
  {
  }

  range_generator(value_type mx) 
    : current(std::numeric_limits<value_type>::min())
    , final(mx)
    , step(value_type(1))
  {
  }

  range_generator(value_type mn, value_type mx) 
    : current(mn)
    , final(mx)
    , step(value_type(1))
  {
  }

  range_generator(value_type mn, value_type mx, value_type stp) 
    : current(mn)
    , final(mx)
    , step(stp)
  {
  }

  iterator begin()
  {
    return iterator(this);
  }
  
  iterator end()
  {
    return iterator();
  }

  virtual bool has_next() const
  {
    if ( step > 0 ) {
      return current <= final;
    }
    else if ( step < 0 ) {
      return current >= final;
    }
    else { // step == 0 is infinite copy of same value
      return true;
    }
  }

  virtual value_type next()
  {
    value_type t = current;
    current += step;
    return t;
  }

private:
  value_type current;
  value_type final;
  value_type step;
  
};

/*!
  \brief Transform a sequence into another sequence
*/
template <typename Iter, typename Trans>
struct transform_adapter : public sequence_adapter<Iter, typename Trans::result_type>
{
  typedef Trans                                  transform_type;
  typedef typename transform_type::argument_type arg_type;
  typedef typename transform_type::result_type   result_type;

  typedef sequence_adapter<Iter, result_type>    base_type;
  typedef typename base_type::base_iterator      base_iterator;
  typedef typename base_type::value_type         value_type;
  typedef typename base_type::adapter_type       adapter_type;
  typedef typename base_type::iterator           iterator;

  transform_adapter(Iter f, Iter t, transform_type fn) 
    : transformer(fn)
    , from(f)
    , to(t)
  {
  }

  iterator begin()
  {
    return iterator(this);
  }
  
  iterator end()
  {
    return iterator();
  }

  virtual bool has_next() const
  {
    return from != to;
  }

  virtual value_type next()
  {
    arg_type a = *from;
    ++from;
    return transformer(a);
  }

private:
  transform_type transformer;
  base_iterator  from;
  base_iterator  to;
};

/*!
  \brief Select a subset of a sequence
*/
template <typename Iter, typename Test>
struct filter_adapter : public sequence_adapter<Iter>
{
  typedef Test                                   test_type;

  typedef sequence_adapter<Iter>                 base_type;
  typedef typename base_type::base_iterator      base_iterator;
  typedef typename base_type::value_type         value_type;
  typedef typename base_type::adapter_type       adapter_type;
  typedef typename base_type::iterator           iterator;

  filter_adapter(Iter f, Iter t, test_type fn) 
    : test(fn)
    , from(f)
    , to(t)
    , cached(false)
  {
    find_next();
  }

  iterator begin()
  {
    return iterator(this);
  }
  
  iterator end()
  {
    return iterator();
  }

  virtual bool has_next() const
  {
    return cached;
  }

  virtual value_type next()
  {
    value_type temp = cached_value;
    find_next();
    return temp;
  }

  void find_next()
  {
    cached = false;
    while ( from != to  ) {
      cached_value = *from;
      if ( test(cached_value) ) {
	cached = true;
	break;
      }
      ++from;
    }
  }

private:
  test_type      test;
  base_iterator  from;
  base_iterator  to;
  bool           cached;
  value_type     cached_value;
};



/// convenience functions

typedef range_generator<unsigned int*> iota_t;

template <typename C>
take_adapter<typename C::iterator> take(C c, size_t n)
{
  typedef take_adapter<typename C::iterator> take_t;
  return take_t(c.begin(), c.end(), n);
}

template <typename C>
drop_adapter<typename C::iterator> drop(C c, size_t n)
{
  typedef drop_adapter<typename C::iterator> drop_t;
  return drop_t(c.begin(), c.end(), n);
}

template <typename C, typename F>
transform_adapter<typename C::iterator, F> transform(C c, F f)
{
  typedef transform_adapter<typename C::iterator, F> transform_t;
  return transform_t(c.begin(), c.end(), f);
}

template <typename C, typename F>
filter_adapter<typename C::iterator, F> filter(C c, F f)
{
  typedef filter_adapter<typename C::iterator, F> filter_t;
  return filter_t(c.begin(), c.end(), f);
}

template <typename C1, typename C2>
void copy(C1 c1, C2 c2)
{
  std::copy(c1.begin(), c1.end(), c2);
}


/// test the take adapter and all the infrastructure on which it is built.

int f(int i)
{
  return 1 + 2 * i;
}

double g(int i)
{
  return ((double) i) / 2.0;
}


int main(int argc, char ** argv)
{
  typedef take_adapter<iota_t::iterator> ta_t;
  typedef drop_adapter<ta_t::iterator>   gen_t;

  std::ostream_iterator<int>    iout(std::cerr, "\n");
  std::ostream_iterator<double> dout(std::cerr, "\n");

  iota_t i;
  ta_t   t(i.begin(), i.end(), 5);
  gen_t  gen(t.begin(), t.end(), 3);
  std::copy(gen.begin(), gen.end(), iout); // hard way
  std::cerr << "\n";

  copy(drop(take(iota_t(),
		 17),
	    13),
       iout);			// easy way
  std::cerr << "\n";

  copy(transform(take(iota_t(), 
		      20), 
		 std::ptr_fun(g)),
       dout);			// test transform
  std::cerr << "\n";

  copy(take(transform(iota_t(), 
		      std::ptr_fun(g)), 
	    20),
       dout);			// commutes
  std::cerr << "\n";

  copy(range_generator<int*>(2, 1, -1),
       iout);
  std::cerr << "\n";

  copy(transform(range_generator<double*>(0, 1, 0.1), 
		 std::ptr_fun(sin)),
       dout);
  std::cerr << "\n";

  copy(transform(range_generator<double*>(0, 1, 0.1), 
		 std::bind1st(std::multiplies<double>(), 3.5)),
       dout);
  std::cerr << "\n";

  copy(take(filter(iota_t(), 
		   std::bind2nd(std::modulus<int>(), 2)), 
	    5),
       dout);			// test filter
}
