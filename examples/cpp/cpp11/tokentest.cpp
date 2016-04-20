
#include <iostream>

#include "streamutils.h"
#include "filetokenstream.h"

using std::cout;
using std::endl;

void tokentest()
{
  FileTokenStream ts(std::string("test_input.txt"));
  dump_stream(ts);
}
