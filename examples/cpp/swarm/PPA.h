#if ! defined(PPA_H)
#define PPA_H 1

class Product;
struct PPAtom;

struct ParticlePositioner
{
  ParticlePositioner(Product * products_, int pcount);
  ~ParticlePositioner();

  int getCount() const;
  double randomize(double * position);
  double update(double * position, double * velocity);

private:
  int count;
  PPAtom * ppa;
  int    * indexer;

  ParticlePositioner(ParticlePositioner const &);
  ParticlePositioner & operator=(ParticlePositioner const &);

  void ppa_start();
  void propagate_bounds(int index, double value);
  double ppa2obj(double * position);

};

#endif
