// $Id: /home/I809989/test/cpp/parser/CharacterStream.h#1 $
// $DateTime: Fri Apr 15 16:42:04 2011 $

#if ! defined(CharacterStream_h)
#define CharacterStream_h 1

#include <string>

namespace parser {
  class CharacterStream
  {
  public:
    CharacterStream();
    virtual ~CharacterStream();
    std::string debug() const;

    char peek() const;
    char getc();
    void ungetc(char c);
    bool eof() const;

    void reset();

  protected:
    char * buf;

  private:
    size_t pos;
  };

  class NullCharacterStream : public CharacterStream
  {
  public:
    NullCharacterStream();
  protected:
  private:
  };
}

#endif // not defined CharacterStream_h
