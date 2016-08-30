
#include <iostream>
#include <limits>

using namespace std;

template <typename T, typename U>
struct TU
{
  T t;
  U u;
};

void sizes()
{
  cout << sizeof( TU<bool, long double> ) << endl;
  cout << sizeof( TU<long double, bool> ) << endl;
  cout << sizeof( bool ) << endl;
  cout << sizeof( char ) << endl;
  cout << sizeof( char16_t ) << endl;
  cout << sizeof( char32_t ) << endl;
  cout << sizeof( wchar_t ) << endl;
  cout << sizeof( short ) << endl;
  cout << sizeof( int ) << endl;
  cout << sizeof( long ) << endl;
  cout << sizeof( long long ) << endl;
  cout << sizeof( float ) << endl;
  cout << sizeof( double ) << endl;
  cout << sizeof( long double ) << endl;
  cout << sizeof( decltype(nullptr) ) << endl;
  cout << endl;
}

template <typename T>
void info()
{
  using info_t = numeric_limits<T>;
  cout << info_t::digits << " " << info_t::digits10 << endl;
  cout << info_t::min() << endl;
  cout << info_t::epsilon() << endl;
  cout << info_t::max() << endl;
  cout << endl;
}

template <typename A, typename B>
void f(const A & a, const B & b)
{
  cout << a << " " << b << endl;
}

template <typename A>
void f(const A & a, const int & b)
{
  for ( int i = 0 ; i < b ; ++i ) {
    cout << a << endl;
  }
}

/**
 * template struct If
 * 
 * Report a type if a condition is true, else nothing
 *
 * Template parameters
 * C -- boolean
 * T -- any type whatsoever
 *
 * The general case (equivalent to C == false) is an empty struct
 * The specialization on C == true defines a type Type as T
 */
template <bool C, typename T>
struct If
{
};

template <typename T>
struct If<true, T>
{
  using Type = T;
};

/**
 * 
 * Report a type depending on a condition being true or false
 *
 * Template parameters
 * C -- boolean
 * T -- any type
 * F -- any type
 *
 * The general case (equivalent to C == false) d
 */
template <bool C, typename T, typename F>
struct IfElse
{
  using Type = typename F::Type;
};

template <typename T, typename F>
struct IfElse<true, T, F>
{
  using Type = T;
};

template <size_t N, typename T, typename... Ts>
struct SizeMatcher
{
  using Type = typename IfElse<N == sizeof(T), T, SizeMatcher<N, Ts...>>::Type;
};

template <size_t N, typename T>
struct SizeMatcher<N, T>
{
  using Type = typename If<N == sizeof(T), T>::Type;
};

template <size_t N>
struct SignedTypeForSize
{
  using Type = typename SizeMatcher<N, char, short, int, long, long long>::Type;
};

template <size_t N>
struct UnsignedTypeForSize
{
  using Type = typename SizeMatcher<N, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>::Type;
};

using Int4 = typename SignedTypeForSize<4>::Type;
using Int8 = typename SignedTypeForSize<8>::Type;

using Uint4 = typename UnsignedTypeForSize<4>::Type;
using Uint8 = typename UnsignedTypeForSize<8>::Type;

int main(int argc, char ** argv)
{
  // sizes();
  info<long double>();
  info<unsigned long long>();
  info<unsigned char>();

  int a = 1234.5;
  double b = 1234U;
  unsigned int c = -1LL;
  const char * d = R"(a\nb)";
  // bool e { 3 };  // won't work with warning -Werror=narrowing
  bool e = 3;       // compiler does not check
  cout << a << " " << b << " " << c << " " << d << boolalpha << " " << e << endl;

  f(true, 3);
  f(true, 3.3);
  cout << endl;

  info<Int4>();
  info<Int8>();

  info<Uint4>();
  info<Uint8>();
  
  return 0;
}
