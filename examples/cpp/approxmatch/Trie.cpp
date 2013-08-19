
#include "Trie.h"

using namespace std;

bool Trie::add(char const * str, size_t const & data)
{
  if ( ! str ) {
    return false;
  }

  return root.put(str, data, 0);
}

bool Trie::has(char const * str) const
{
  if ( ! str ) {
    return false;
  }

  size_t x;
  return root.get(str, 0, x);
}

size_t Trie::count() const
{
  return root.count();
}

size_t Trie::value(char const * str) const
{
  if ( ! str ) {
    throw std::runtime_error("bad key in Trie");
  }

  size_t x;
  if ( root.get(str, 0, x) ) {
    return x;
  }

  throw std::runtime_error("missing key in Trie");
}

size_t Trie::match(std::map<std::string, MatchData> & matches,
		 char const * pattern,
		 size_t maxError) const
{
  PartialMatchData p;
  return root.match(matches, pattern, maxError, p, 0);
}
