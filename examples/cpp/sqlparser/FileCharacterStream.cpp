// $Id: /home/I809989/test/cpp/parser/FileCharacterStream.cpp#1 $
// $DateTime: Mon Apr 18 11:13:49 2011 $

#include <sstream>
#include <stdexcept>
#include <fstream>

#include "FileCharacterStream.h"

using namespace std;
using namespace parser;


FileCharacterStream::FileCharacterStream(string const & name)
{
    ifstream input(name.c_str());
    if ( ! input.good() ) {
      stringstream s;
      s << "Failed to open file " << name;
      throw runtime_error(s.str());
    }

    input.seekg(0, ios::end);
    int size = (int) input.tellg();
    input.seekg(0, ios::beg);

    if ( size > (1024 * 1024) ) {
      stringstream s;
      s << "input file is too big: " << size
	<< " (limit is " << (1024 * 1024) << ")";
      throw runtime_error(s.str());
    }

    buf = new char[size + 1];
    input.read(buf, size);
    buf[size] = '\0';
    input.close();
}
