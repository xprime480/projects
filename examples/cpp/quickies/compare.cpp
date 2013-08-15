
#include <iostream>

#define FIELD_COMPARATOR_0 return false;

#define FIELD_COMPARATOR_1(other, f1) \
if (f1 != other.f1) \
  return f1 < other.f1; \
FIELD_COMPARATOR_0 ;

#define FIELD_COMPARATOR_2(other, f1, f2) \
if (f1 != other.f1) \
  return f1 < other.f1; \
FIELD_COMPARATOR_1(other, f2) ;

#define FIELD_COMPARATOR_3(other, f1, f2, f3) \
if (f1 != other.f1) \
  return f1 < other.f1; \
FIELD_COMPARATOR_2(other, f2, f3) ;

class TWIC {
public:
  TWIC(int i_, int j_, int k_);
  bool operator < (TWIC const & that) const;
private:
  int i;
  int j;
  int k;
};


TWIC::TWIC(int i_, int j_, int k_)
  : i(i_)
  , j(j_)
  , k(k_)
{
}

bool TWIC::operator < (TWIC const & that) const
{
  FIELD_COMPARATOR_3(that, i, j, k);
}

int main(int argc, char ** argv) 
{
  TWIC twic1(1,2,3);
  TWIC twic2(1,2,4);
  std::cout << (twic1 < twic2) << std::endl;
  std::cout << (twic2 < twic1) << std::endl;
  std::cout << (twic1 < twic1) << std::endl;
  return 0;
}
