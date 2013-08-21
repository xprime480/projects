#if ! defined(List_h)
#define List_h 1

#include <vector>

#include "LazySeq.h"

/**
 * List
 *
 * This class lazily builds a sequence from a given list of items.
 * 
 * Examples:
 *  () -> ()
 *  (1 1 1) -> (1 1 1)
 *
 */
template <typename T = int>
class List : public LazySeq<T>
{
public:
  /*
   * constructor
   *
   * create the list from some data sort which has a begin and end
   * iterator.
   *
   * @param _data the input data
   */ 
  template <typename U>
  List(U & _data)
    : LazySeq<T>()
    , data(_data.begin(), _data.end())
  {
    if ( ! data.empty() ) {
      this->head = *data.begin();
      this->empty = false;
    }
  }

  /**
   * tail
   *
   * See base class for documentation.
   */ 
  virtual LazySeq<T> * tail()
  {
    LazySeq<T> * z = NULL;
    if ( this->empty ) {
      z = new NullSeq<T>();
    }
    else {
      typename std::vector<T> v(++data.begin(), data.end());
      z = new List<T>(v);
    }

    TRACEALLOC(z);
    return z;
  }

private:
  typename std::vector<T> data;	// a copy of the input data
};

#endif // not defined List_h
