#if ! defined(Particle_h)
#define Particle_h 1

class Product;
class Rules;
struct ParticlePositioner;

class Particle
{
public:
  Particle(ParticlePositioner & pp);
  ~Particle();

  void next(double * pos, ParticlePositioner & pp);
  void update(double * pos, double & obj) const;

  void report() const;

protected:
private:
  int       count;
  double *  position;
  double *  velocity;
  double *  local_max;
  double    local_max_objective;

  Particle(Particle const &);
  Particle & operator=(Particle const &);
};

#endif
