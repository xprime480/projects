// $Id: /home/I809989/test/cpp/parser/TokenStream.h#1 $
// $DateTime: Fri Apr 15 16:13:00 2011 $

#if ! defined(TokenStream_h)
#define TokenStream_h 1

#include <vector>

namespace parser {

  class Token;
  class CharacterStream;

  class TokenStream
  {
  public:
    typedef int state_type;

    TokenStream(CharacterStream & _c);
    virtual ~TokenStream();

    Token * get() const;
    void forward();
    void back();

    state_type getState() const;
    void setState(state_type state);

  protected:
    size_t linenumber;

    char peek() const;
    char getc();
    void ungetc(char c);
    bool eof() const;

    virtual bool isSymbolChar(char c);
    virtual bool isDigitChar(char c);
    virtual bool isQuoteChar(char c);
    virtual bool isEol(char c);
    virtual bool isSpace(char c);

    char skipws();

    virtual Token * getNextToken() = 0;
    
  private:
    CharacterStream & chars;

    std::vector<Token *> tokens;
    state_type pos;
  };

  class NullTokenStream : public TokenStream
  {
  public:
    NullTokenStream(CharacterStream & _c);

  protected:
    virtual Token * getNextToken();
    
  private:
  };
}

#endif // not defined TokenStream_h
