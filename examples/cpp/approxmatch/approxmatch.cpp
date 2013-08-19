
#include <iostream>

#include "levenshtein.h"
#include "DistanceWithTranspose.h"

using namespace std;


namespace {
  void usage()
  {
    cout << "approxmatch str1 str2" << endl;
  }
}

int main(int argc, char ** argv)
{
  if ( argc < 3 ) {
    usage();
    return 1;
  }

  size_t l = levenshtein(argv[1], argv[2]);
  DistanceWithTranspose dwt(argv[1], argv[2]);
  size_t d = dwt.distance();
  cout << argv[1] << ", " << argv[2] << " ==> " << l << " " << d << endl;
  
  return 0;
}
