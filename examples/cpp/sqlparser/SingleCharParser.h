// $Id: /home/I809989/test/cpp/parser/SingleCharParser.h#1 $
// $DateTime: Fri Apr 15 10:28:35 2011 $

#if ! defined(SingleCharParser_h)
#define SingleCharParser_h 1

#include "Parser.h"

namespace parser {

  class SingleCharParser : public Parser
  {
  public:
    SingleCharParser(char _c);

    virtual Expression parse(TokenStream & tokens, int flags) const;

  private:
    std::string c;
  };

}

#endif // not defined SingleCharParser_h
