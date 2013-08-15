
#include <iostream>
#include <tr1/tuple>

template<int i, typename... T>
class Foo
{
};

struct False
{
  static const bool value = false;
};

struct True
{
  static const bool value = true;
};

template<typename T> struct IsIntegral : public False {};
#define DEFINE_AS_INTEGRAL(T) \
template<> struct IsIntegral<T> : public True {};

DEFINE_AS_INTEGRAL(char)
DEFINE_AS_INTEGRAL(signed char)
DEFINE_AS_INTEGRAL(unsigned char)

DEFINE_AS_INTEGRAL(short);
DEFINE_AS_INTEGRAL(unsigned short);

DEFINE_AS_INTEGRAL(int);
DEFINE_AS_INTEGRAL(unsigned int);

DEFINE_AS_INTEGRAL(long);
DEFINE_AS_INTEGRAL(unsigned long);

DEFINE_AS_INTEGRAL(long long);
DEFINE_AS_INTEGRAL(unsigned long long);


template<typename T, typename U> class SameType : public False {};
template<typename T> class SameType<T, T> : public True {};

template<typename T>
void printValue()
{
  std::cout << T::value << std::endl;
}

template<typename T>
void printValue(T const & _)
{
  printValue<T>();
}



int main(int argc, char ** argv)
{
  printValue<SameType<int, int> >();
  printValue<SameType<int, bool> >();

  printValue<IsIntegral<int> >();
  printValue<IsIntegral<unsigned char> >();
  printValue<IsIntegral<double> >();

  std::tr1::tuple<int, char**> x(argc, argv);
  std::cout << std::tr1::get<0>(x) << std::endl;
  std::cout << (*std::tr1::get<1>(x)) << std::endl;
  return 0;
}
