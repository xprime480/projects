
#include <iostream>

template<typename T, typename... Rest>
struct Foo
{
  static int const value = sizeof(T) + Foo<Rest...>::value;
};

template<typename T>
struct Foo<T>
{
  static int const value = sizeof(T);
};

template<>
struct Foo<void>
{
  static int const value = 0;
};

int main(int argc, char ** argv)
{
  std::cout << Foo<int, double, char *>::value << std::endl;
  return 0;
}

