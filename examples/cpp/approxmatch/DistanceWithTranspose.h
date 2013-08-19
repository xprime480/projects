#if ! defined(DistanceWithTranspose_h)
#define DistanceWithTranspose_h 1

#include <vector>
#include <set>

#include "Score.h"

class DistanceWithTranspose
{
public:
  DistanceWithTranspose(char const * _s, char const * _t);

  size_t distance();

private:
  char const * const s;
  char const * const t;
  size_t lenS;
  size_t lenT;
  mutable std::vector<Score *> scores;
  bool computed;
  size_t val;
  size_t inserts;
  size_t best;

  void init_scores();

  void compute();

  void clear();

  bool empty() const;
  Score & get();
  void insert(Score & score);
};

#endif // not defined DistanceWithTranspose_h
