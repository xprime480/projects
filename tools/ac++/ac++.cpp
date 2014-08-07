
#include <exception>
#include <iostream>
#include <string>

#include "ArgParser.h"
#include "Formatter.h"
#include "TextFormatter.h"
#include "LatexFormatter.h"
#include "Analyzer.h"

using namespace std;
using namespace ArgParser;

/*
 * Read inputs and analyze columns.
 */	
int main(int argc, char const ** argv)
{
  ArgumentParser parser;

  Argument format("--format", OPTIONAL);
  format.setDefault("latex");
  format.setHelp("Stat output format (latex or text)");
  parser.addArgument(format);

  Argument files("files", REMAINDER);
  files.setHelp("CSV input files");
  parser.addArgument(files);

  Formatter * formatter = 0;
  vector<string> inputs;
  try {
    ParsedArgs const args = parser.parseArgs(--argc, ++argv);
    string const argFormat = args["format"].to_string();
    if ( argFormat == "text" ) {
      formatter = new TextFormatter;
    }
    else {
      formatter = new LatexFormatter;
    }
    inputs = args["files"].to_string_list();
  }
  catch ( exception & e ) {
    cerr << e.what();
    return 1;
  }

  Analyzer analyzer(*formatter);
  analyzer.read(inputs);
  analyzer.write();

  delete formatter;

  return 0;
}
