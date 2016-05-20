#if ! defined(DUSCOMPUTER_H)
#define DUSCOMPUTER_H 1

#include <cstddef>
#include <vector>

#include "generator.h"

class DusComputer
{
public:
  using factor_type = const std::vector<double>;
  using dus_type = std::vector<double>;

  DusComputer( const double base, factor_type factors );

  void compute();
  const dus_type & results() const;

private:
  const double base;
  factor_type factors;
  dus_type dus;

  static std::vector<int> memo_fact;

  double compute_ix(size_t ix) const;
};

#endif // DUSCOMPUTER_H
