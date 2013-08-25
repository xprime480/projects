#if ! defined( Token_h )
#define Token_h 1

#include <string>

class Token
{
public:
  typedef enum {
    TT_KWD, 
    TT_VAR, 
    TT_NUM, 
    TT_LPAREN,
    TT_RPAREN,
    TT_EQ,
    TT_PLUS,
    TT_MINUS,
    TT_TIMES,
    TT_DIVS,
    TT_POWER,
    TT_COMMA,

    TT_EOF
  }
  TokenType;

  Token( char c, TokenType tt );
  Token( std::string const & s, TokenType tt );
  std::string const & value() const;
  TokenType type() const;

private:
  std::string v;
  TokenType   t;
  
};

bool operator==( Token const & t1, Token const & t2 );
inline bool operator!=( Token const & t1, Token const & t2 ) 
{
  return ! ( t1 == t2 ); 
}

std::ostream & operator<<( std::ostream & os, Token const & t );

#endif
