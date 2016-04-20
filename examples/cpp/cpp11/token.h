#if ! defined(TOKEN_H)
#define TOKEN_H 1

#include <string>

class Token
{
public:

 Token(std::string & value);
  
  std::string format() const;

private:
  const std::string value;
};

namespace std
{
  template <typename O>
  O & operator<<(O & os, const Token & token)
  {
    return os << token.format();
  }
}

#endif // TOKEN_H
