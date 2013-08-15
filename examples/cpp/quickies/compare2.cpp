
#include <iostream>

#include "field_comparator.h"

/*
 * that which is compared
 */
class TWIC {
public:
  TWIC(int i_, int j_, int k_);
  bool operator < (TWIC const & that) const;
private:
  int i;
  int j;
  int k;
};


/*
 * implement ctor
 */
TWIC::TWIC(int i_, int j_, int k_)
  : i(i_)
  , j(j_)
  , k(k_)
{
}

/*
 * implement < operator
 */
bool TWIC::operator < (TWIC const & that) const
{
  return field_comparator(*this, that, &TWIC::i, &TWIC::j, &TWIC::k);
}

/*
 * test driver
 */
int main(int argc, char ** argv) 
{
  TWIC twic1(1,2,3);
  TWIC twic2(1,2,4);
  std::cout << (twic1 < twic2) << std::endl;
  std::cout << (twic2 < twic1) << std::endl;
  std::cout << (twic1 < twic1) << std::endl;
  return 0;
}
