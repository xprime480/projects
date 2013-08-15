#if ! defined(Tester_h)
#define Tester_h 1

#include <vector>
#include <set>

#include "Collector.h"

class Tester {
public:
  Tester(int size);

  void run(int tries);
  void report() const;
protected:
private:
  int max;
  std::vector< Collector > counts;
  std::set< int > seen;

  void runonce();
};


#endif
