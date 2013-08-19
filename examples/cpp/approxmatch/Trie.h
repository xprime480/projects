#if ! defined(Trie_h)
#define Trie_h 1

#include <cstdlib>
#include <stdexcept>
#include <map>
#include <string>

#include "TrieNode.h"
#include "MatchData.h"

class Trie
{
public:
  /**
   * add
   *
   * Add a string to a trie.  Assumes that \a this is the root.
   *
   * @param str  string to add to trie.
   * @param data data associated with string
   *
   * @return true iff the string was added.  (Particularly:  false if
   *         the string was already in the trie.)
   */
  bool add(char const * str, size_t const & data);

  /**
   * has
   *
   * Check if a given string is in the trie.
   *
   * @param str string to look for.
   *
   * @param return true iff the string is found.
   */
  bool has(char const * str) const;

  /**
   * count
   *
   * return the number of strings in the trie.
   *
   * @return the count
   */
  size_t count() const;

  /**
   * value
   *
   * Get the value associated with a string
   *
   * @param str string to look for.
   *
   * @param return value if found.  Undefined behavior if not found.
   */
  size_t value(char const * str) const;

  /**
   * match
   *
   * Find approximate matches in the trie.
   *
   * @param matches  store the matches
   * @param pattern  target pattern
   * @param maxError number of errors to allow before giving up
   * 
   * @return the number of calls made
   */
  size_t match(std::map<std::string, MatchData> & matches,
	       char const * pattern,
	       size_t maxError) const;

private:
  /**
   * root of the trie
   */
  TrieNode root;
};

#endif // not defined Trie_h
