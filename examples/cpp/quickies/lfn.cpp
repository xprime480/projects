
//
// This program won't compile as is
//

#include <functional>
#include <stdexcept>
#include <iostream>

namespace Utils
{
  struct end_of_values : public std::overflow_error
  {
    end_of_values() 
      : std::overflow_error("No more items in the list")
    {
    }
  };

  template <typename _Result>
  struct nullary_function
  {
    typedef _Result result_type;
  };

  template <typename _Result>
  struct generator : public nullary_function<_Result>
  {
    typedef typename nullary_function<_Result>::result_type result_type;

    result_type operator()()
    {
      throw end_of_values();
      return _Result(0);
    }
  };

  template <typename _Result>
  struct iota : public generator<_Result>
  {
    typedef typename generator<_Result>::result_type result_type;

    iota() 
      : current(1)
    {
    }

    result_type operator()()
    {
      result_type temp = current;
      current = current + 1;
      return temp;
    }

  private:
    result_type current;
    
  };


  template <typename _Gen>
  struct take : public generator<typename _Gen::result_type>
  {
    typedef _Gen generator_type;
    typedef typename generator_type::result_type result_type;

    take(size_t count, generator_type g) 
      : taken(0)
      , max(count)
      , gen(g)
    {
    }

    result_type operator()()
    {
      if ( taken >= max ) {
	throw end_of_values();
      }
      ++taken;
      return gen();
    }

  private:
    size_t         taken;
    size_t const   max;
    generator_type gen;
  };

  template <typename _Gen>
  struct drop : public generator<typename _Gen::result_type>
  {
    typedef _Gen generator_type;
    typedef typename generator_type::result_type result_type;

    drop(size_t count, generator_type g) 
      : gen(g)
    {
      for ( size_t x = 0 ; x < count ; ++x ) {
	// go ahead and throw them away now
	gen();
      }
    }

    result_type operator()()
    {
      return gen();
    }

  private:
    generator_type gen;
  };


  template <typename _Fn, typename _Gen>
  struct filter : public generator<typename _Gen::result_type>
  {
    typedef _Fn func_type;
    typedef _Gen generator_type;
    typedef typename generator_type::result_type result_type;

    filter(func_type t, generator_type g)
      : test(t)
      , gen(g)
    {
    }

    result_type operator()()
    {
      while ( true ) {
	result_type t = gen();
	if ( test(t) ) {
	  return t;
	}
      }
    }

  private:
    func_type      test;
    generator_type gen;
  };

  template <typename _Fn, typename _Gen>
  filter<_Fn, _Gen> make_filter(_Fn f, _Gen g)
  {
    return filter<_Fn, _Gen>(f, g);
  }
}

bool is_odd(int & i) 
{
  return i%2 == 1;
}

bool is_even(int & i) 
{
  return i%2 == 0;
}


int main(int main, char ** argv)
{
  typedef Utils::iota<int>    Gen1;
  typedef Utils::drop<Gen1>   Gen2;
  typedef Utils::take<Gen2>   Gen3;
  
  Gen1  g1;
  Gen2  g2(29, g1);
  Gen3  g3(5, g2);
  auto gen = Utils::make_filter(std::ptr_fun(&is_odd), g3);

  try {
    for ( int x = 0 ; x < 10 ; ++ x ) {
      std::cerr << gen() << "\n";
    }
  }
  catch ( Utils::end_of_values e ) {
    std::cerr << e.what() << "\n";
  }
}
