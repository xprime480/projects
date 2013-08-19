#if ! defined(TokenStream_h)
#define TokenStream_h 1

#include <string>

#include "LazySeq.h"
#include "Token.h"

namespace lazy
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
    std::string rest;		// unscanned input

    /**
     * skipWS
     * 
     * Trim leading whitespace from the pending input.
     */
    void skipWS();

    /**
     * getUnaryOperator
     *
     * Find out the length of any unary operator at the beginning of
     * unscanned input.
     *
     * @return 0 if the beginning of input is not a unary operator, or
     *         the size of the operator if it is one.
     */
    size_t getUnaryOperator();

    /**
     * getBinaryOperator
     *
     * Find out the length of any binary operator at the beginning of
     * unscanned input.
     *
     * @return 0 if the beginning of input is not a binary operator, or
     *         the size of the operator if it is one.
     */
    size_t getBinaryOperator();

    /**
     * getKeyword
     *
     * Find out the length of any keyword at the beginning of
     * unscanned input. 
     *
     * @return 0 if the beginning of input is not a keyword, or the
     *         size of the keyword if it is one. 
     */
    size_t getKeyword();

    /**
     * getInteger
     *
     * Find out the length of any integer at the beginning of
     * unscanned input.
     *
     * @return 0 if the beginning of input is not an integer, or the
     *         size of the integer if it is one. 
     */
    size_t getInteger();
  };
}

#endif // not defined TokenStream_h
