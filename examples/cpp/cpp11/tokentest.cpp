
#include <iostream>

#include "streamutils.h"
#include "filetokenstream.h"

using std::cout;
using std::endl;

void tokentest(int argc, char ** argv)
{
  FileTokenStream ts(std::string("test_input.txt"));
  dump_stream(ts);
}
