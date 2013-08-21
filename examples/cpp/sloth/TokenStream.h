#if ! defined(TokenStream_h)
#define TokenStream_h 1

#include <string>

#include "LazySeq.h"
#include "Token.h"

namespace Sloth
{
  /**
   * TokenStream
   *
   * A lazy stream of tokens
   */
  class TokenStream : public LazySeq<Token>
  {
  public:
    /**
     * constructor
     *
     * Create an empty token stream.
     */
    TokenStream();

    /**
     * constructor
     *
     * Create a token stream from textual input
     *
     * @param input the input
     */
    TokenStream(std::string const & input);

    /**
     * destructor
     */
    virtual ~TokenStream();

    /**
     * tail
     *
     * See base class for documentation.
     */ 
    TokenStream * tail();

  private:
}

#endif // not defined TokenStream_h
