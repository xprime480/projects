// $Id: /home/I809989/test/cpp/parser/BasicTokenStream.h#1 $
// $DateTime: Fri Apr 15 16:22:41 2011 $

#if ! defined(BasicTokenStream_h)
#define BasicTokenStream_h 1

#include <string>

#include "TokenStream.h"

namespace parser {
  class CharacterStream;	// where our input comes from
  class Token;

  /**
   * BasicTokenStream
   *
   * This class takes a stream of characters and lexes it into a
   * stream of tokens.  The following rules are observed:
   *
   * TOKEN_SYMBOL:  starts with isSymbolChar() character and contains
   *                all following sequence of symbol and digit
   *                characters.
   * TOKEN_FLOAT:   starts with a digit, and contains all following
   *                digits, a decimal point, and optional additional
   *                digits. 
   * TOKEN_INT:     starts with a digit, and contains all following
   *                digits. 
   * TOKEN_TEXT:    A quote character, all following characters up to
   *                next unescaped matching quote character
   * TOKEN_LDELIM:  A left paren, square bracket or curly brace
   * TOKEN_RDELIM:  A right paren, square bracket or curly brace
   * TOKEN_OPER:    +, =, *, /, =, <, >, +=, -=, *=, /=, <=, >=, ==,
   *                >>, or <<
   * TOKEN_EOL:     End of line character
   * TOKEN_UNKNOWN: Anything else
   *
   * Whitespace is skipped, except in text tokens.
   */
  class BasicTokenStream : public TokenStream
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
    BasicTokenStream(CharacterStream & chars);

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
    /**
     * isLeftChar
     *
     * Report if a given character is the left hand of a matching
     * delimiter pair such a parenthesis, square bracket, or curly
     * brace.
     *
     * @param c a character
     *
     * @return true if the input is a left delimiter
     */
    bool isLeftChar(char c) const;

    /**
     * isRightChar
     *
     * Report if a given character is the right hand of a matching
     * delimiter pair such a parenthesis, square bracket, or curly
     * brace.
     *
     * @param c a character
     *
     * @return true if the input is a right delimiter
     */
    bool isRightChar(char c) const;

    /**
     * isOperChar
     *
     * Report if a given character is the first character of an
     * operator sequence.
     *
     * @param c a character
     *
     * @return true if the input is the start of an operator
     */
    bool isOperChar(char c) const;

    /**
     * tokenizeSymbol
     *
     * Produce a token for a symbol.  (See above for definition.)
     *
     * @param buf A string with the first character of the symbol
     *
     * @return the newly created token, owned by the caller
     */
    Token * tokenizeSymbol(std::string & buf);

    /**
     * tokenizeNumeric
     *
     * Produce a token for a numeric type, either FLOAT or INTEGER.
     * (See above for definition.) 
     *
     * @param buf A string with the first character of the number.
     *
     * @return the newly created token, owned by the caller
     */
    Token * tokenizeNumeric(std::string & buf);

    /**
     * tokenizeText
     *
     * Produce a token for quoted text. (See above for definition.)
     *
     * @param delim the delimiter that will terminate the string.
     *
     * @return the newly created token, owned by the caller
     */
    Token * tokenizeText(char delim);


    /**
     * tokenizeOperator
     *
     * Produce a token for an operator.  (See above for definition.) 
     *
     * @param buf A string with the first character of the operation.
     *
     * @return the newly created token, owned by the caller
     */
    Token * tokenizeOperator(std::string & buf);
  };
}

#endif // not defined BasicTokenStream_h
