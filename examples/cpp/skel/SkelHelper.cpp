
#include <iostream>

#include "SkelHelper.h"

using namespace std;

int skel_helper(int argc, char **argv)
{
  for ( int i = 0 ; i < argc ; ++i ) {
    cout << argv[i] << endl;
  }

  return 0;
}

