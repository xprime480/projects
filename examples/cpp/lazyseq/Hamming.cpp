#include <vector>

#include "Hamming.h"
#include "List.h"

using namespace std;

Hamming::Hamming()
  : GeneralizedHamming(getGenerators())
{
}

LazySeq<int> * Hamming::getGenerators()
{
  static int g[] = { 2, 3, 5 };
  static vector<int> v(g, g+3);
  static LazySeq<int> * gg = new List<int>(v);
  return gg;
}
