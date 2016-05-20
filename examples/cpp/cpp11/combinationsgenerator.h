#if ! defined (COMBINATIONSGENERATOR_H)
#define COMBINATIONSGENERATOR_H 1

#include <vector>

#include "streamutils.h"

template <typename U>
class CombinationsGenerator
{
public:
  using data_type = std::vector<typename U::value_type>;
  using base_type = CombinationsGenerator<U>;

  CombinationsGenerator(const U & data)
  {
    for ( const auto & v : data ) {
      all.push_back(v);
    }
  }

  class Iterator
  {
  public:
    using base_type = const CombinationsGenerator<U> *;
    using data_type = CombinationsGenerator<U>::data_type;

    Iterator(base_type base, size_t from)
      : base(base)
      , current(from)
    {
    }

    bool operator!=(const Iterator & other) const
    {
      return base != other.base || current != other.current;
    }

    Iterator operator++() 
    {
      ++current;
      return *this;
    }
    
    data_type operator*() const
    {
      return base ? base->get_subset(current) : data_type();
    }

  private:
    base_type base;
    size_t current;
  };

  Iterator begin() const
  {
    Iterator iter(this, 0);
    return iter;
  }

  Iterator end() const
  {
    Iterator iter(this, 1 << all.size());
    return iter;
  }

  data_type get_subset(size_t mask) const
  {
    data_type tmp;

    for ( size_t ix = 0 ; mask && ix <= all.size() ; ++ix ) {
      const size_t selector = (1<<ix);
      if ( mask & selector ) {
	tmp.push_back(all[ix]);
	mask ^= selector;
      }
    }

    return tmp;
  }

private:

  data_type all;
};

#endif // COMBINATIONSGENERATOR_H 
