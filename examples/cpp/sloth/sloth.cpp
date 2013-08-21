
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Interp.h"

using namespace std;
using namespace Sloth;

namespace
{
  void process(Interp & interp, istream & s)
  {
    string const quit("quit");
    char command[2000] ;
    while ( s.good() ) {
      s.getline(command, 2000);
      if ( string("") == command ) {
	continue;
      }
      if ( quit == command ) {
	break;
      }
      try {
	interp.parse(command);
      }
      catch ( exception & e ) {
	cerr << "Caught error: " << e.what() << endl;
      }
    }
  }
}

int main(int argc, char ** argv)
{
  string const commandArg("-c");
  Interp interp;

  if ( argc > 1 ) {
    --argc;
    ++argv;
    if ( commandArg == *argv ) {
      --argc;
      ++argv;

      stringstream s;
      while ( *argv ) {
	s << *argv++ << " ";
      }
      interp.parse(s.str().c_str());
      interp.parse("print");
    }

    else {
      ifstream lines(*argv);
      if ( lines ) {
	process(interp, lines);
      }
      else {
	cerr << "Error opening command file " << *argv << endl;
      }
    }
  }

  else {
    process(interp, cin);
  }

  return 0;
}
