// $Id: /home/I809989/test/cpp/parser/CharTokenStream.h#1 $
// $DateTime: Mon Apr 18 13:19:52 2011 $

#if ! defined(CharTokenStream_h)
#define CharTokenStream_h 1

#include "TokenStream.h"

namespace parser {
  class CharacterStream;

  class CharTokenStream : public TokenStream
  {
  public:
    CharTokenStream(CharacterStream & chars);

  protected:
    virtual Token * getNextToken();

  private:
  };
}

#endif // not defined CharTokenStream_h
