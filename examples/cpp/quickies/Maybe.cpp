
#include <stdexcept>
#include <iostream>

/**
 * This demonstrates an expensive way to pretend to be Haskell.
 */

template <typename T>
struct Maybe
{
  Maybe()
    : bottom(true)
  {
  }

  Maybe(T const & v)
    : bottom(false)
    , value(v)
  {
  }

  bool isBottom() const
  {
    return bottom;
  }

  operator T() const
  {
    if ( bottom ) {
      throw std::runtime_error("casting bottom");
    }
    return value;
  }

private:
  bool bottom;
  T    value;
  
};

using namespace std;

template <typename T>
Maybe<T> operator+(T      const & a, T      const & b)
{
  return Maybe<T>(a) + Maybe<T>(b);
}

template <typename T>
Maybe<T> operator+(Maybe<T> const & a, T      const & b)
{
  return a + Maybe<T>(b);
}

template <typename T>
Maybe<T> operator+(T      const & a, Maybe<T> const & b)
{
  return Maybe<T>(a) + b;
}

template <typename T>
Maybe<T> operator+(Maybe<T> const & a, Maybe<T> const & b)
{
  if ( (! a.isBottom()) && (! b.isBottom()) ) {
    T aa = a;
    T bb = b;
    return Maybe<T>(aa + bb);
  }
  
  return Maybe<T>();
}

template <typename T>
Maybe<T> operator-(T      const & a, T      const & b)
{
  return Maybe<T>(a) - Maybe<T>(b);
}

template <typename T>
Maybe<T> operator-(Maybe<T> const & a, T      const & b)
{
  return a - Maybe<T>(b);
}

template <typename T>
Maybe<T> operator-(T      const & a, Maybe<T> const & b)
{
  return Maybe<T>(a) - b;
}

template <typename T>
Maybe<T> operator-(Maybe<T> const & a, Maybe<T> const & b)
{
  if ( (! a.isBottom()) && (! b.isBottom()) ) {
    double aa = a;
    double bb = b;
    return Maybe<T>(aa - bb);
  }
  
  return Maybe<T>();
}

template <typename T>
Maybe<T> operator*(T      const & a, T      const & b)
{
  return Maybe<T>(a) * Maybe<T>(b);
}

template <typename T>
Maybe<T> operator*(Maybe<T> const & a, T      const & b)
{
  return a * Maybe<T>(b);
}

template <typename T>
Maybe<T> operator*(T      const & a, Maybe<T> const & b)
{
  return Maybe<T>(a) * b;
}

template <typename T>
Maybe<T> operator*(Maybe<T> const & a, Maybe<T> const & b)
{
  if ( (! a.isBottom()) && (! b.isBottom()) ) {
    double aa = a;
    double bb = b;
    return Maybe<T>(aa * bb);
  }
  
  return Maybe<T>();
}

template <typename T>
Maybe<T> operator/(T      const & a, T      const & b)
{
  return Maybe<T>(a) / Maybe<T>(b);
}

template <typename T>
Maybe<T> operator/(Maybe<T> const & a, T      const & b)
{
  return a / Maybe<T>(b);
}

template <typename T>
Maybe<T> operator/(T      const & a, Maybe<T> const & b)
{
  return Maybe<T>(a) / b;
}

template <typename T>
Maybe<T> operator/(Maybe<T> const & a, Maybe<T> const & b)
{
  if ( (! a.isBottom()) && (! b.isBottom()) ) {
    double aa = a;
    double bb = b;
    if ( bb != 0.0 ) {
      return Maybe<T>(aa / bb);
    }
  }
  
  return Maybe<T>();
}

typedef Maybe<double> safe_double; 
static safe_double bottom;

void test(safe_double const & a, 
	  safe_double const & b, 
	  safe_double (* pfn)(safe_double const & a, safe_double const & b), 
	  char const * label)
{
  safe_double result = pfn(a,b);
  if ( result.isBottom() ) {
    cout << "bad " << label << endl;
  }
  else {
    cout << (double) result << endl;
  }
}

void test(safe_double const & a, safe_double const & b)
{
  test(a, b, &operator/, "divide");
  test(a, b, &operator*, "multiply");
  test(a, b, &operator+, "add");
  test(a, b, &operator-, "subtract");
}


int main(int argc, char ** argv)
{
  safe_double a(1.0);
  safe_double b(2.0);
  safe_double x;		// bottom
  safe_double z(0.0);		// for divide-by-zero test

  test(a,b);
  test(a,z);
  test(b,x);

  cout << (3.0 / z) << endl;
}
