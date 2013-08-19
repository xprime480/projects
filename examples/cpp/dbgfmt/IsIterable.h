#if !defined(IsIterable_h)
#define IsIterable_h 1

#include <vector>
#include <map>
#include <list>

template<typename T>
struct IsIterable
{
  static bool const value = false;
};

template<typename T>
struct IsIterable<std::vector<T> >
{
  static bool const value = true;
};

template<typename T>
struct IsIterable<std::list<T> >
{
  static bool const value = true;
};

template<typename K, typename V>
struct IsIterable<std::map<K, V> >
{
  static bool const value = true;
};

#endif
