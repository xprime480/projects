#if ! defined(TrieNode_h)
#define TrieNode_h 1

#include <cstdlib>
#include <map>
#include <string>

#include "MatchData.h"

class TrieNode
{
public:
  /**
   * constructor
   *
   * Make an empty node.
   */
  TrieNode();

  /**
   * copy constructor
   *
   * @param t node to copy
   */
  TrieNode(TrieNode const & t);

  /**
   * destructor
   *
   * Clean up a node
   */
  ~TrieNode();

  /**
   * put
   *
   * traverse one level down the trie either inserting the key or
   * traversing to the next node toward its insertion point.
   *
   * @param str  the string to add
   * @param data data associated with the string
   * @param pos  the index in the string of the current level key.
   *
   * @return true iff the string was newly added to the trie.
   */
  bool put(char const * str, size_t data, size_t pos);

  /**
   * get
   *
   * find a string in the trie.
   *
   * @param str the string to find
   * @param pos the index in the string of the current level key.
   * @param v   holder for value if found
   *
   * @return true iff the string was found in this subtree.
   */
  bool get(char const * str, size_t pos, size_t & v) const;

  /**
   * count
   *
   * return the number of strings in the trie branch.
   *
   * @return the count
   */
  size_t count() const;

  /**
   * match
   *
   * Find approximate matches in the trie.
   *
   * @param matches  store the matches
   * @param pattern  target pattern
   * @param maxError number of errors to allow before giving up
   * @param partial  a match in progress
   * @param pos      the index in the string of the current level key.
   *
   * @return the number of calls tried
   */
  size_t match(std::map<std::string, MatchData> & matches,
	       char const * pattern,
	       size_t maxError,
	       PartialMatchData const & partial,
	       size_t pos) const;

protected:
  /**
   * key the key represeted by a node.  If null, the current node only
   * holds pointers to longer strings.
   */
  char * key;

  /**
   * value holds the data associated with the key.
   */
  size_t value;

  /**
   * The next level of keys.  Index is an char.
   */
  std::map<char, TrieNode> children;
};

#endif // not defined TrieNode_h
