// $Id: /home/I809989/test/cpp/parser/CharTokenStream.h#1 $
// $DateTime: Mon Apr 18 13:19:52 2011 $

#if ! defined(CharTokenStream_h)
#define CharTokenStream_h 1

#include "TokenStream.h"

namespace parser {
  class CharacterStream;	// where our input comes from

  /**
   * CharTokenStream
   *
   * This class takes a stream of characters and lexes it into a
   * stream of tokens.  Each non-whitespace character is a separate
   * token of type TOKEN_TEXT.
   */
  class CharTokenStream : public TokenStream
  {
  public:
    /**
     * constructor
     *
     * Create a token stream from a character stream.
     *
     * @param _c a character stream
     *
     */
    CharTokenStream(CharacterStream & chars);

  protected:
    /**
     * getNextToken
     *
     * Reads enough input from the character stream to produce the
     * next token.  Returns NULL if EOF is reached.
     *
     * @return a pointer to a token, owned by the caller.
     */
    virtual Token * getNextToken();

  private:
  };
}

#endif // not defined CharTokenStream_h
