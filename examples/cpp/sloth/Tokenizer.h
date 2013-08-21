#if ! defined(Tokenizer_h)
#define Tokenizer_h 1

#include <deque>
#include <string>

#include "Token.h"

namespace Sloth
{
  class Tokenizer
  {
  public:
    Tokenizer();
    void tokenize(std::string const & input);

    bool empty() const;
    Token front() const;
    void next();

  private:
    mutable std::deque<Token> tokens;
    mutable std::string rest;		// unscanned input

    void lex() const;

    /**
     * skipWS
     * 
     * Trim leading whitespace from the pending input.
     */
    void skipWS() const;

    /**
     * getOperator
     *
     * Find out the length of any operator at the beginning of
     * unscanned input.  An operatory is any string that starts with a
     * non-keyword or non-reserved character, and is terminated by a
     * keyword character or a reserved character.
     *
     * @return 0 if the beginning of input is not a unary operator, or
     *         the size of the operator if it is one.
     */
    size_t getOperator() const;

    /**
     * getKeyword
     *
     * Find out the length of any keyword at the beginning of
     * unscanned input. 
     *
     * @return 0 if the beginning of input is not a keyword, or the
     *         size of the keyword if it is one. 
     */
    size_t getKeyword() const;

    /**
     * getInteger
     *
     * Find out the length of any integer at the beginning of
     * unscanned input.
     *
     * @return 0 if the beginning of input is not an integer, or the
     *         size of the integer if it is one. 
     */
    size_t getInteger() const;

    /**
     * getString
     *
     * Find out the length of any quoted string at the beginning of
     * unscanned input.
     *
     * @return 0 if the beginning of input is not a quoted string, or
     *         the size of the string (including delimiters) if it is
     *         one.
     */
    size_t getString() const;

    /**
     * getSymbol
     *
     * Find out the length of any symbol (:foo) at the beginning of
     * unscanned input.
     *
     * @return 0 if the beginning of input is not a symbol, or the
     * size of the symbol if it is one.
     */
    size_t getSymbol() const;

    /**
     * getBoolean
     *
     * Find out the length of any boolean constant (#t or #f) at the
     * beginning of unscanned input.
     *
     * @return 0 if the beginning of input is not a symbol, or the
     * size of the constant if it is one.
     */
    size_t getBoolean() const;
  };
}

#endif // not defined Tokenizer_h
