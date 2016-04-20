
#include "filetokenstream.h"

using std::string;

FileTokenStream::FileTokenStream(const string & filename)
  : in(filename)
{
}

FileTokenStream::~FileTokenStream()
{
  if ( in ) {
    in.close();
  }
}

void FileTokenStream::fillBuffer(char * buf, size_t & buf_sz)
{
  if ( ! in || ! in.good() ) {
    buf_sz = 0;
    return;
  }

  in.read(buf, buf_sz);
  buf_sz = in.gcount();
}
