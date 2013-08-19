#if ! defined(Token_h)
#define Token_h 1

#include <string>

namespace lazy
{
  /**
   * Token
   *
   * This class represents a token scanned from an input source.
   */
  class Token
  {
  public:
    /**
     * constructor 
     */
    Token()
      : type(TT_UNKNOWN)
    {
    }

    /**
     * known token types
     */
    enum { TT_UNKNOWN = 0,
	   TT_KEYWORD,
	   TT_UNARY_OPERATOR,
	   TT_BINARY_OPERATOR,
	   TT_INTEGER,
	   TT_LPAREN,
	   TT_RPAREN,
	   TT_LSQUARE,
	   TT_RSQUARE,
	   TT_PLACEHOLDER
    } type;

    std::string contents;	// text as scanned

  };
}

/**
 * operator<<
 *
 * send a representation of the token to a stream.
 *
 * @param os the stream
 * @param t  a token
 *
 * @return the input stream
 */
template <typename OS>
OS & operator<<(OS & os, lazy::Token const & t)
{
  os << t.contents;
  return os;
}

#endif // not defined Token_h
