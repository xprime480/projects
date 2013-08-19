
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

#include "Trie.h"
#include "MatchData.h"

using namespace std;

void test1()
{
  Trie trie;

  assert( 0 == trie.count() );

  assert( trie.add("test", 1) );	// something to start with
  assert( trie.add("best", 2 ) );	// differs initially
  assert( trie.add("bess", 3 ) );	// differs finally
  assert( trie.add("bes",  4 ) );	// prefix of existing
  assert( trie.add("bass", 5 ) );	// differs internally
  assert( trie.add("tests", 6 ) );	// extenstion of existing
  assert( ! trie.add("test", 7) );	// duplicate

  assert ( 1 == trie.value("test") ); // values should be correct

  assert( trie.has("test") );	// has it
  assert( trie.has("tests") );	// has it
  assert( ! trie.has("fail") );	// has it not

  assert( ! trie.has("") );	// has it not
  assert( trie.add("", 8) );	// add it
  assert( trie.has("") );	// has it now

  assert( 7 == trie.count() );	// accurate count;

  cout << "All tests passed" << endl;
}

void test2(int argc, char ** argv)
{
  Trie trie;

  if ( argc < 2 ) {
    return;
  }

  char const * filename = argv[1];
  std::ifstream input(filename);
  if ( ! input.good() ) {
    std::cerr << "could not open " << filename << std::endl;
    return;
  }

  std::string token;
  size_t read = 0;

  for ( ;; ) {
    input >> token;
    if ( input.eof() ) {
      break;
    }
    
    ++read;
    trie.add(token.c_str(), read);
  }

  std::cout << read << " tokens read" << std::endl;
  std::cout << trie.count() << " tokens inserted" << std::endl;

  if ( argc < 3 ) {
    return;
  }

  map<string, MatchData> matches;
  size_t maxErr = max(2, (int) (1 + (2 * sqrt(strlen(argv[2])) ) / 5));
  size_t calls = trie.match(matches, argv[2], maxErr);
  cout << "Used " << calls << " calls" << endl;
  map<string, MatchData>::const_iterator iter;
  for ( iter = matches.begin() ; iter != matches.end() ; ++iter ) {
    cout << iter->second << endl;
  }
}

int main(int argc, char ** argv) 
{
  test1();
  test2(argc, argv);

  return 0;
}


