// $Id: /home/I809989/test/cpp/parser/BasicTokenStream.h#1 $
// $DateTime: Fri Apr 15 16:22:41 2011 $

#if ! defined(BasicTokenStream_h)
#define BasicTokenStream_h 1

#include "TokenStream.h"


namespace parser {
  class CharacterStream;

  class BasicTokenStream : public TokenStream
  {
  public:
    BasicTokenStream(CharacterStream & chars);

  protected:
    virtual Token * getNextToken();

  private:
    bool isLeftChar(char c) const;
    bool isRightChar(char c) const;
    bool isOperChar(char c) const;

    Token * tokenizeSymbol(std::string & buf);
    Token * tokenizeNumeric(std::string & buf);
    Token * tokenizeText(char delim);
    Token * tokenizeOperator(std::string & buf);
  };
}

#endif // not defined BasicTokenStream_h
