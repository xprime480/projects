
#include <fstream>

#include "TSP.h"

using namespace std;

void TSP::read(std::string const & inputFile)
{
  ifstream pointSource(inputFile.c_str());
}

void TSP::solve()
{
}

void TSP::write(std::string const & outputFile) const
{
  ofstream pointSource(outputFile.c_str());
}
