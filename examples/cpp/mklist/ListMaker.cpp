#include <set>
#include <time.h>
#include <cstring>
#include <algorithm>
#include <memory>

#include "util.h"
#include "UniformGenerator.h"
#include "ExponentialGenerator.h"

#include "ListMaker.h"

using namespace std;

ListMaker::ListMaker()
{
  initVars();
}

ListMaker::ListMaker(int argc, char ** argv)
{
  initVars();
  parseArgs(argc, argv);
}

vector<int> ListMaker::make()
{
  set<int> ns;

  if ( lim <= output ) {
    for ( size_t i = 1 ; i <= lim ; ++i ) {
      ns.insert(i);
    }
  }
  else {
    srand(time(0));

    for ( size_t i = 1 ; i <= prefix ; ++i ) {
      ns.insert(i);
    }

    auto_ptr<Generator> gen(makeGenerator());
    while ( ns.size() < output ) {
      ns.insert(gen->gen());
    }
  }

  vector<int> ls(ns.begin(), ns.end());
  if ( ! sorted ) {
    randomize(ls);
  }

  return ls;
}

void ListMaker::initVars()
{
  lim         = 50;
  sorted      = false;
  output      = 10;
  prefix      = 5;
  middle      = lim/3;
  exponential = false;
}

void ListMaker::parseArgs(int argc, char ** argv)
{
  while ( argc > 0 && *argv && **argv == '-' ) {
    char const * flag = *argv;
    --argc;
    ++argv;

    if ( strlen(flag) < 2 ) {
      break;
    }

    char flagchar = flag[1];
    switch ( flagchar ) {
    case 's' :
      sorted = true;
      break;

    case 'l' :
      lim = getNumericArg(argc, argv, lim);
      break;

    case 'o' :
      output = getNumericArg(argc, argv, output);
      break;

    case 'p' :
      prefix = getNumericArg(argc, argv, prefix);
      break;

    case 'e' :
      exponential = true;
      middle = getNumericArg(argc, argv, lim/3);
    }
  }

  lim = getNumericArg(argc, argv, lim); // for backwards compatibility

  if ( output > lim ) {
    output = lim;
  }
  if ( prefix > output ) {
    prefix = output;
  }

  if ( exponential && middle >= lim/2 ) {
    middle = lim/2 - 1;
  }
}

void ListMaker::randomize(vector<int> & p)
{
  random_shuffle(p.begin(), p.end());
}


Generator * ListMaker::makeGenerator() const
{
  if ( exponential ) {
    return new ExponentialGenerator(1, lim, middle);
  }
  else {
    return new UniformGenerator(1 + prefix, lim);
  }

  return 0;
}
