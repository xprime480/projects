// $Id: /home/I809989/test/cpp/parser/Token.h#1 $
// $DateTime: Fri Apr 15 16:14:26 2011 $

#if ! defined(Token_h)
#define Token_h 1

#include <string>

namespace parser {

  class Token {
  public:
    typedef enum {
      TOKEN_UNKNOWN = 0,
      TOKEN_TEXT    = 1,
      TOKEN_SYM, 
      TOKEN_OPER,
      TOKEN_INT,
      TOKEN_FLOAT,
      TOKEN_LDELIM,
      TOKEN_RDELIM,
      TOKEN_EOL     = 999,
      TOKEN_USER_0  = 1000
    } types;

    Token(types _typ, std::string const & _txt);

    types getType() const;
    std::string const & getText() const;

  protected:

  private:
    types       type;
    std::string text;
  };

}

#endif // not defined Token_h
