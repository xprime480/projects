#if ! defined(Rules_h)
#define Rules_h 1

#include <vector>

class Product;

class Rules
{
public:
  Rules(Product const * products_, int pcount_);

  bool test(double * rates) const;

protected:

private:
  typedef std::pair<int, int>   RuleType;
  typedef std::vector<RuleType> RuleSetType;

  RuleSetType rules;
  
  Product const * products;
  int pcount;
};

#endif
