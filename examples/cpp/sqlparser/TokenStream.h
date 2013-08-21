// $Id: /home/I809989/test/cpp/parser/TokenStream.h#1 $
// $DateTime: Fri Apr 15 16:13:00 2011 $

#if ! defined(TokenStream_h)
#define TokenStream_h 1

#include <vector>

namespace parser {

  class Token;			// what we are producing
  class CharacterStream;	// where our input comes from

  /**
   * TokenStream
   *
   * PURE VIRTUAL CLASS
   *
   * This class takes a stream of characters and lexes it into a
   * stream of tokens.  The default version has simple rules for
   * lexing.
   *
   * The model is that as long as the end of the character stream has
   * not been reached, there is a "current" token which can be read
   * multiple times.  The stream pointer can also be moved back or
   * forward.  The current state can be read or set multiple times in
   * any order.  Reading from the character stream is lazy in the
   * sense that only moving the token stream past its current end
   * causes any character reads to be attempted.
   */
  class TokenStream
  {
  public:
    /**
     * type to describe our internal state.  Should be opaque to
     * clients.
     */
    typedef int state_type;

    /**
     * constructor
     *
     * Create a token stream from a character stream.
     *
     * @param _c a character stream
     *
     */
    TokenStream(CharacterStream & _c);

    /**
     * desctructor
     */
    virtual ~TokenStream();

    /**
     * get
     *
     * Get a pointer to the current token.
     *
     * @return a pointer to the current token, or NULL if past EOS. 
     */
    Token * get() const;

    /**
     * forward
     *
     * Move the current token stream pointer forward, reading a new
     * token if necessary.
     */
    void forward();

    /**
     * back
     *
     * Move the current token stream pointer backward.  If the token
     * stream is at the beginning of the stream when the function is
     * called, a runtime_error is thrown.
     *
     */
    void back();

    /**
     * getState
     *
     * Get the current state of the token stream, suitable for passing
     * to \a setState to restore the current state.
     *
     * @return an opaque value representing the state.
     */
    state_type getState() const;

    /**
     * setState
     *
     * Restore the current state of the token stream to a value
     * previously retrieved by \a getState.  Behavior is undefined if
     * any other value is passed as a parameter.
     *
     * @param state a value previously read with \a getState
     */
    void setState(state_type state);

  protected:
    /**
     * Line number of the last read character
     */
    size_t linenumber;

    /**
     * peek
     *
     * look at the next character in the input
     *
     * @return the next character, -1 for EOF.
     */
    char peek() const;

    /**
     * getc
     *
     * fetch the next character in the input, advancing the pointer
     *
     * @return the next character, -1 for EOF.
     */
    char getc();

    /**
     * ungetc
     *
     * back up the input stream, putting the given character in the
     * input stream.
     *
     * @param c a character to insert in the input stream.
     */
    void ungetc(char c);

    /**
     * eof
     *
     * Report if the character stream is at the end
     *
     * @return true if current and future calls to the \a get function
     *         will return EOF (-1)
     */
    bool eof() const;

    /**
     * isSymbolChar
     *
     * Report if a given character is a symbol constituent in the
     * current lexer.
     *
     * @param c a character
     *
     * @return true if the input is a symbol character
     */
    virtual bool isSymbolChar(char c);

    /**
     * isDigitChar
     *
     * Report if a given character is a digit in the current lexer.
     *
     * @param c a character
     *
     * @return true if the input is a digit character
     */
    virtual bool isDigitChar(char c);

    /**
     * isQuoteChar
     *
     * Report if a given character begins and ends a quoted string in
     * the current lexer.
     *
     * @param c a character
     *
     * @return true if the input is a quote character
     */
    virtual bool isQuoteChar(char c);

    /**
     * isQuoteChar
     *
     * Report if a given character ends lines in the current lexer.
     *
     * @param c a character
     *
     * @return true if the input ends a line
     */
    virtual bool isEol(char c);

    /**
     * isQuoteChar
     *
     * Report if a given character constitutes whitespace in the
     * current lexer.
     *
     * @param c a character
     *
     * @return true if the input is whitespace
     */
    virtual bool isSpace(char c);

    /**
     * skipws
     *
     * Advances the current character stream to the first
     * non-whitespace character (or EOF).   Uses the definition of
     * whitespace provided by \a isSpace.
     *
     * @return the following non-whitespace character.
     */
    char skipws();

    /**
     * getNextToken
     *
     * Reads enough input from the character stream to produce the
     * next token.  Returns NULL if EOF is reached.
     *
     * @return a pointer to a token, owned by the caller.
     */
    virtual Token * getNextToken() = 0;
    
  private:
    /**
     * Source of input
     */
    CharacterStream & chars;

    /**
     * previously scanned tokens
     */
    std::vector<Token *> tokens;

    /**
     * current position in \tokens
     */
    state_type pos;
  };


  /**
   * NullTokenStream
   *
   * A TokenStream which always returns end of input tokens
   */
  class NullTokenStream : public TokenStream
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
    NullTokenStream(CharacterStream & _c);

  protected:
    /**
     * getNextToken
     *
     * Reads enough input from the character stream to produce the
     * next token.  Returns NULL if EOF is reached.
     *
     * @return Always NULL.
     */
    virtual Token * getNextToken();
    
  private:
  };
}

#endif // not defined TokenStream_h
