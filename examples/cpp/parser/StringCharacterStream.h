// $Id: /home/I809989/test/cpp/parser/StringCharacterStream.h#1 $
// $DateTime: Mon Apr 18 09:47:06 2011 $

#if ! defined(StringCharacterStream_h)
#define StringCharacterStream_h 1

#include "CharacterStream.h"

namespace parser {
  class StringCharacterStream : public CharacterStream
  {
  public:
    StringCharacterStream(char const * _c);
  protected:
  private:
  };
}

#endif // not defined StringCharacterStream_h
