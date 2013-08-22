
#include <iostream>
#include <fstream>

size_t const COLUMN_WIDTH = 18;
size_t const NUM_COLS = 4;
size_t const LINE_WIDTH = COLUMN_WIDTH * NUM_COLS;
size_t const GUTTER_WIDTH = 2;
char const GUTTER_CHAR = ' ';

void fmt( std::istream & is ) 
{
  static size_t current_col( 0 );
      
  for ( ;; ) {
    std::string word;
    is >> word;
    if ( word.empty() ) {
      break;
    }
    size_t const word_width = word.size();
  REPEAT:
    size_t temp = current_col * COLUMN_WIDTH + word_width + GUTTER_WIDTH;
    if ( temp >= LINE_WIDTH ) {
      if ( 0 == current_col ) {
	std::cout << word << "\n";
      }
      else { 
	std::cout << "\n";
	current_col = 0;
	goto REPEAT;
      }
    }
    else {
      size_t sizemod = word.size() % COLUMN_WIDTH;
      size_t pad = COLUMN_WIDTH - sizemod;
      if ( pad < GUTTER_WIDTH ) {
	pad += COLUMN_WIDTH;
      }
      word += std::string( pad, GUTTER_CHAR );
      std::cout << word;

      size_t cols_used = word.size() / COLUMN_WIDTH;
      current_col += cols_used;
    }
  }
}

int main( int argc, char ** argv ) 
{
  if ( 1 == argc ) {
    fmt( std::cin );
  }
  else {
    for ( int i = 1 ; i < argc ; ++i ) {
      std::ifstream f( argv[i] );
      fmt( f );
    }
  }
  std::cout << "\n";
  return 0;
}
