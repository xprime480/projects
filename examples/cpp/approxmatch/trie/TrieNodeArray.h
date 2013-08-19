#if ! defined(TrieNodeArray_h)
#define TrieNodeArray_h 1

#include <algorithm>
#include <cstring>
#include <cassert>

#include "TrieNode.h"

template <typename DATA>
class TrieNodeArray : public TrieNode<DATA>
{
public:
  /**
   * constructor
   *
   * Make an empty node.
   */
  TrieNodeArray()
    : TrieNode<DATA>()
  {
    fill_n(children, 256, (TrieNodeArray*) NULL);
  }

  /**
   * destructor
   *
   * Clean up a node
   */
  virtual ~TrieNodeArray()
  {
    if ( key ) {
      free(key);
      key = (char *) NULL;
    }

    for ( size_t i = 0 ; i < 256 ; ++i ) {
      if ( children[i] ) {
	delete children[i];
	children[i] = (TrieNodeArray *) NULL;
      }
    }
  }

  /**
   * put
   *
   * see base class for doc
   */
  virtual bool put(char const * str, DATA const & data, size_t pos)
  {
    char const ch = str[pos];
    if ( ! ch ) {
      if ( ! key ) {
	key = strdup(str);
	return true;
      }
      assert(0 == strcmp(key, str));
      return false;
    }

    size_t idx = (size_t) ch;
    if ( ! children[idx] ) {
      children[idx] = new TrieNodeArray;
    }
    return children[idx]->put(str, pos+1);
  }

  /**
   * get
   *
   * see base class for doc
   */
  bool get(char const * str, size_t pos) const
  {
    char const ch = str[pos];
    if ( ! ch ) {
      if ( ! key ) {
	return false;
      }
      assert(0 == strcmp(key, str));
      return true;
    }

    size_t idx = (size_t) ch;
    if ( ! children[idx] ) {
      return false;
    }
    return children[idx]->get(str, pos+1);
  }

  /**
   * count
   *
   * see base class for doc
   */
  size_t count() const
  {
    size_t c = 0;
    if ( key ) {
      ++c;
    }

    for ( size_t i = 0 ; i < 256 ; ++i ) {
      if ( children[i] ) {
	c += children[i]->count();
      }
    }

    return c;
  }

private:
  /**
   * The next level of keys.  Index is an char.
   */
  TrieNodeArray * children[256];
};

#endif // not defined TrieNodeArray_h
