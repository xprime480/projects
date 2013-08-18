#if ! defined(Swarm_h)
#define Swarm_h 1

#include <vector>

#include "Rules.h"
#include "PPA.h"

class Product;
class Particle;

class Swarm
{
public:
  Swarm(Product * products_, int pcount, int scount);
  ~Swarm();

  void iterate(int maxPass, int stable, bool dump = false);
  void next();
  void report() const;

protected:
private:

  std::vector<Particle *> swarm;

  Product * products;
  int count;

  double * position_max;
  double   objective_max;
  
  Swarm(Swarm const &);
  Swarm & operator=(Swarm const &);

  ParticlePositioner pp;
};

#endif
