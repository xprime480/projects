// $Id: /home/I809989/test/cpp/parser/AnyCharOfParser.h#1 $
// $DateTime: Fri Apr 15 10:50:55 2011 $

#if ! defined(AnyCharOfParser_h)
#define AnyCharOfParser_h 1

#include "Parser.h"

namespace parser {
  class AnyCharOfParser : public Parser
  {
  public:
    AnyCharOfParser(std::string const & _cs);

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    std::string charset;
  };

  extern std::string const lowercase;
  extern std::string const uppercase;
  extern std::string const digits;
  extern std::string const hexdigits;
  extern std::string const whitespace;

}

#endif // not defined AnyCharOfParser_h
