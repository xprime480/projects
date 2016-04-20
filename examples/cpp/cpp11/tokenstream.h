#if ! defined(TOKENSTREAM_H)
#define TOKENSTREAM_H 1

#include <string>

#include "token.h"
#include "generator.h"

constexpr size_t BUFSIZE = 1024;

class TokenStream : public Generator<Token>
{
public:
  TokenStream();

  Token operator()();

protected:
  virtual void fillBuffer(char * buf, size_t & buf_sz) = 0;

private:
  char buffer[1024];
  size_t bufp;
  size_t buf_sz;

  std::string ws;

  void skip_ws();
};

#endif // TOKENSTREAM_H
