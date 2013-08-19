#if ! defined(trietester_h)
#define trietester_h 1

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "Trie.h"

void test1(Trie & trie)
{
  assert( 0 == trie.count() );

  assert( trie.add("test", 1) );	// something to start with
  assert( trie.add("best", 2 ) );	// differs initially
  assert( trie.add("bess", 3 ) );	// differs finally
  assert( trie.add("bes",  4 ) );	// prefix of existing
  assert( trie.add("bass", 5 ) );	// differs internally
  assert( trie.add("tests", 6 ) );	// extenstion of existing
  assert( ! trie.add("test", 7) );	// duplicate

  assert( trie.has("test") );	// has it
  assert( trie.has("tests") );	// has it
  assert( ! trie.has("fail") );	// has it not

  assert( ! trie.has("") );	// has it not
  assert( trie.add("", 8) );	// add it
  assert( trie.has("") );	// has it now

  assert( 7 == trie.count() );	// accurate count;
}

void test2(Trie & trie, int argc, char ** argv)
{
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
}

#endif // not defined trietester_h
