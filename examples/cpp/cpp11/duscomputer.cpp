
#include <set>
#include <iostream>

#include "range.h"
#include "streamutils.h"
#include "combinationsgenerator.h"

#include "duscomputer.h"

using std::set;
using std::cout;
using std::endl;
using std::vector;

DusComputer::DusComputer( const double base, factor_type factors )
  : base(base)
  , factors(factors)
  , dus(factors.size(), 0.0)
{
  
  for ( size_t i = memo_fact.size() ; i <= factors.size() ; ++i ) {
    memo_fact.push_back(i * memo_fact[i-1]);
  }
}

void DusComputer::compute()
{
  Range<size_t> pre_ix(0, factors.size(), 1);
  auto indexes = collect(pre_ix);
  
  for ( auto ix : indexes ) {
    dus[ix] = compute_ix(ix);
  }
}

const DusComputer::dus_type & DusComputer::results() const
{
  return dus;
}

double DusComputer::compute_ix(size_t ix) const
{
  double dus_for_ix = 0.0;
  const double factor_for_ix = factors[ix];
  const size_t factor_size = factors.size();
  
  using index_set = set<size_t>;
  index_set index_wo_ix;
  for ( size_t i = 0 ; i < factor_size ; ++i ) {
    if ( i != ix ) {
      index_wo_ix.insert(i);
    }
  }
  CombinationsGenerator<index_set> combinations(index_wo_ix);

  for ( const auto combination : combinations ) {
    double us = base;
    for ( const auto cix : combination ) {
      us *= factors[cix];
    }
    const double us_with_ix = us * factor_for_ix;
    const double delta = us_with_ix - us;
    const size_t combo_size = combination.size();
    const int multiplier = memo_fact[combo_size] * memo_fact[factor_size - combo_size - 1];
    const double value = multiplier *  delta;
    dus_for_ix += value;
  }

  return dus_for_ix / (memo_fact[factors.size()]);
}

vector<int> DusComputer::memo_fact(2, 1);
