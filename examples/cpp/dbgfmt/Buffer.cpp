#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>

#include "strdup.h"

#include "Buffer.h"

template<typename OS>
void test(OS & os)
{
  char temp[20];
  std::auto_ptr<Buffer> buf(makeStreamBuffer(os));
  sprintf(temp, "%10s  %10s  ", "N", "N*N");
  buf->setHeader(temp);
  for ( int i = 1 ; i < 100 ; ++i ) {
    buf->pushState();
    sprintf(temp, "%10d  ", i);
    buf->append(temp);
    sprintf(temp, "%10d  ", (i*i));
    buf->append(temp);
    buf->writeData();
    buf->popState();
  }
}

int main(int argc, char ** argv)
{
  test(std::cerr);
  std::ofstream f("BufferTest.txt");
  test(f);

  return 0;
}
