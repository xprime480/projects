#if ! defined(TrieNodeMap_h)
#define TrieNodeMap_h 1

#include <cstring>
#include <map>

#include "TrieNode.h"

template <typename DATA>
class TrieNodeMap : public TrieNode<DATA>
{
public:
  /**
   * destructor
   *
   * Clean up a node
   */
  virtual ~TrieNodeMap()
  {
    if ( key ) {
      free(key);
      key = (char *) NULL;
    }
  }

  /**
   * put
   *
   * see base class for doc
   */

private:
};

#endif // not defined TrieNodeMap_h
