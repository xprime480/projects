
#include "util.h"

size_t getNumericArg(int & argc, char ** & argv, size_t def)
{
  if ( argc <= 0 ) {
    return def;
  }
  if ( ! argv || ! *argv ) {
    return def;
  }

  size_t rv = atoi(*argv);

  --argc;
  ++argv;

  return rv;
}


