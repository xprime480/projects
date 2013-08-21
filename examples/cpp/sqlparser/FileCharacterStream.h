// $Id: /home/I809989/test/cpp/parser/FileCharacterStream.h#1 $
// $DateTime: Fri Apr 15 16:41:04 2011 $

#if ! defined(FileCharacterStream_h)
#define FileCharacterStream_h 1

#include <string>

#include "CharacterStream.h"

namespace parser {
  class FileCharacterStream : public CharacterStream
  {
  public:
    FileCharacterStream(std::string const & name);

  protected:
  private:
  };
}

#endif // not defined FileCharacterStream_h
