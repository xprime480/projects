#if ! defined(DEFAULT_VALUES_H)
#define DEFAULT_VALUES_H 1

#include <type_traits>

template <typename T, bool useint, bool usenoarg>
struct DV
{
  static T get_default_value()
  {
    throw "No suitable default value";
  }
};

template <typename T, bool usenoarg>
struct DV<T, true, usenoarg>
{
  static T get_default_value()
  {
    static T value{ 0 };
    return value;
  }
};

template <typename T>
struct DV<T, false, true>
{
  static T get_default_value()
  {
    static T value;
    return value;
  }
};

template <typename T>
T get_default_value()
{
  using std::is_constructible;
  constexpr bool int_constr   = is_constructible<T, int>::value;
  constexpr bool noarg_constr = ! int_constr && is_constructible<T>::value;
  using builder = DV<T, int_constr, noarg_constr>;

  return builder::get_default_value();
}



#endif  // DEFAULT_VALUES_H
