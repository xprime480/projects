#if ! defined( Parser_h )
#define Parser_h 1

#include <iosfwd>
#include <map>

#include "Token.h"

class Equation;

class Parser
{
public:
  Parser( std::istream & s );
  Equation * parse();
private:
  typedef std::map< char, size_t > symbol_table_t;

  std::istream & input;
  symbol_table_t symbols;
  std::vector< Token > token_stream;
  size_t next_token;

  bool accept( Token const & t );
  void parse_prelude();
  void parse_varlist();
  Equation * parse_eqn();
  void assert_eof();
  Token const & peek();
  bool lex();
  void fill_buffer( std::string & buffer );
  void lex_number( std::string & buffer );
};

#endif
