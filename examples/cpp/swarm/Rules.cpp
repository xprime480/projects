
#include <iostream>
#include <set>

#include "Products.h"
#include "Rules.h"

Rules::Rules(Product const * products_, int pcount_)
  : products(products_)
  , pcount(pcount_)
{
  typedef std::pair<int, int>        ProdOrdering;
  typedef std::set<ProdOrdering>     OrderedSet;
  typedef OrderedSet::const_iterator Iter;

  OrderedSet order;
  for ( int i = 0 ; i < pcount ; ++i ) {
    order.insert(std::make_pair(products[i].getMinRate(), 
				products[i].getKey()));
  }

  Iter pEnd = order.end();
  Iter pos  = order.begin();
  if ( pEnd == pos ) {
    return;
  }
  int prev = pos->second;
  for ( ++pos ; pos != pEnd ; ++pos ) {
    int curr = pos->second;
    rules.push_back(RuleType(prev, curr));
    std::cerr << "Rule " << prev << " < " << curr << "\n";
    prev = curr;
  }
}


bool Rules::test(double * rates) const
{
  typedef RuleSetType::const_iterator RSI;

  RSI rEnd = rules.end();
  for ( RSI pos = rules.begin() ;  pos != rEnd ; ++pos ) {
    int i1 = pos->first  - 1;
    int i2 = pos->second - 1;
    if ( rates[i1] > rates[i2] ) {
      return false;
    }
  }

  return true;
}
