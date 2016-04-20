#if ! defined(FILETOKENSTREAM_H)
#define FILETOKENSTREAM_H 1

#include <string>
#include <fstream>

#include "tokenstream.h"

class FileTokenStreamImpl;

class FileTokenStream : public TokenStream
{
public:
  FileTokenStream(const std::string & filename);
  ~FileTokenStream();

protected:
  void fillBuffer(char * buf, size_t & buf_sz);

private:
  std::ifstream in;
};

#endif // FILETOKENSTREAM_H
