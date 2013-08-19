
#include <cstring>

#include "TrieNode.h"

using namespace std;

char * strdup(char const * s) 
{
  if ( ! s ) {
    return 0;
  }

  size_t len = strlen(s);
  char * news = (char *) malloc(1 + len);
  strcpy(news, s);

  return news;
}

TrieNode::TrieNode()
  : key(0)
  , value(0)
{
}

TrieNode::TrieNode(TrieNode const & t)
  : key(t.key ? strdup(t.key) : 0)
  , value(t.value)
{
}

TrieNode::~TrieNode()
{
  if ( key ) {
    free(key);
    key = NULL;
  }
}

bool TrieNode::put(char const * str, size_t data, size_t pos)
{
  char const ch = str[pos];
  if ( ! ch ) {
    if ( ! key ) {
      key = strdup(str);
      value = data;
      return true;
    }
    return false;
  }

  return children[ch].put(str, data, pos+1);
}

bool TrieNode::get(char const * str, size_t pos, size_t & v) const
{
  char const ch = str[pos];
  if ( ! ch ) {
    if ( key == NULL ) {
      return false;
    }

    v = value;
    return true;
  }

  // size_t idx = (size_t) ch;
  map<char, TrieNode>::const_iterator iter = children.find(ch);
  if ( iter == children.end() ) {
    return false;
  }
  return iter->second.get(str, pos+1, v);
}

size_t TrieNode::count() const
{
  size_t c = 0;
  if ( key ) {
    ++c;
  }

  map<char, TrieNode>::const_iterator iter;
  for ( iter = children.begin() ; iter != children.end() ; ++iter ) {
    c += iter->second.count();
  }

  return c;
}

size_t TrieNode::match(map<string, MatchData> & matches,
		       char const * pattern,
		       size_t maxError,
		       PartialMatchData const & partial,
		       size_t pos) const
{
  size_t calls = 1;

  if ( partial.score > maxError ) {
    return calls;
  }

  /**
   * if we are testing a transpose, see if we can finish it
   */
  if ( partial.inTranspose ) {
    map<char, TrieNode>::const_iterator iter;
    iter = children.find(partial.transposeChar);
    if ( iter != children.end() ) {
      PartialMatchData p = partial;
      p.inTranspose = false;
      p.score++;
      calls += iter->second.match(matches, pattern, maxError, p, pos+1);
    }
  
    return calls;
  }

  size_t patternLeft = strlen(pattern + partial.pos);

  /**
   * if we have a key here, it may match
   */
  if ( key ) {
    MatchData m;
    m.score = partial.score + patternLeft;
    if ( m.score <= maxError ) {
      m.key = key;
      m.value = value;
      map<string, MatchData>::iterator i = matches.find(key);
      if ( i == matches.end() ) {
	matches[key] = m;
      }
      else {
	if ( m.score < i->second.score ) {
	  i->second = m;
	}
      }
    }
  }

  /**
   * if there are at least two characters in the pattern test a transpose
   */
  if ( patternLeft >= 2 ) {
    PartialMatchData p = partial;
    char ch1 = pattern[p.pos];
    char ch2 = pattern[p.pos + 1];
    
    if ( ch1 != ch2 ) {
      map<char, TrieNode>::const_iterator iter;
      iter = children.find(ch2);
      if ( iter != children.end() ) {
	p.pos += 2;
	p.inTranspose = true;
	p.transposeChar = ch1;
	calls += iter->second.match(matches, pattern, maxError, p, pos+1);
      }
    }
  }

  /**
   * loop over all the child characters.  If they are equal, advance,
   * otherwise test an insert, a substitution and a delete.
   */
  char const current = pattern[partial.pos];
  map<char, TrieNode>::const_iterator iter;
  for ( iter = children.begin() ; iter != children.end() ; ++iter ) {
    if ( current == iter->first ) {
      PartialMatchData p = partial;
      p.pos++;
      calls += iter->second.match(matches, pattern, maxError, p, pos+1);
    }
    else {
      // first, delete/substitute from the pattern
      if ( patternLeft != 0 ) {
	PartialMatchData p = partial;
	p.score++;
	p.pos++;
	calls += match(matches, pattern, maxError, p, pos); // the delete
	calls += iter->second.match(matches, pattern, maxError, p, pos+1);
      }
      
      // next, insert into the pattern
      {
	PartialMatchData p = partial;
	p.score++;
	calls += iter->second.match(matches, pattern, maxError, p, pos+1);
      }
    }
  }

  return calls;
}
