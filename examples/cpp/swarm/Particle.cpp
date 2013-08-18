
#include <cmath>
#include <iostream>

#include "Utils.h"
#include "Products.h"
#include "Rules.h"
#include "Particle.h"
#include "PPA.h"

Particle::Particle(ParticlePositioner & pp)
  : count(pp.getCount())
  , position(new double[count])
  , velocity(new double[count])
  , local_max(new double[count])
  , local_max_objective(0.00)
{
  local_max_objective = pp.randomize(position);
  for ( int i = 0 ; i < count ; ++i ) {
    random_value(velocity[i], -3.0, +3.0);
    local_max[i] = position[i];
  }
}

Particle::~Particle()
{
  delete [] position;
  delete [] velocity;
  delete [] local_max;
}

void Particle::next(double * pos, ParticlePositioner & pp)
{
  double new_objective = 0.0;
#if 0
  for ( int i = 0 ; i < count ; ++i ) {
    position[i] = position[i] + velocity[i];
    if ( position[i] < (double) products[i].getMinRate() ) {
      position[i] = (double) products[i].getMinRate();
    }
    if ( position[i] > (double) products[i].getMaxRate() ) {
      position[i] = (double) products[i].getMaxRate();
    }
    new_objective += products[i].objective((int) (0.5 + position[i]));
  }

#else
  new_objective = pp.update(position, velocity);
#endif

  if ( new_objective > local_max_objective ) {
    local_max_objective = new_objective;
    for ( int i = 0 ; i < count ; ++i ) {
      local_max[i] = position[i];
    }
  }


  double const inertia = 0.9;
  double const local_pressure = 1.0;
  double const global_pressure = 1.0;
  double       local_r;
  double       global_r;
  random_value(local_r, 0.0, 1.0);
  random_value(global_r, 0.0, 1.0);

  for ( int i = 0 ; i < count ; ++i ) {
    double jitter;
    random_value(jitter, -1.0, +1.0);
    velocity[i] = ( inertia * velocity[i] +
		    local_pressure * local_r * (local_max[i] - position[i]) +
		    global_pressure * global_r * (pos[i] - position[i]) +
		    jitter);
  }
}

void Particle::update(double * pos, double & obj) const
{
  if ( local_max_objective > obj ) {
    obj = local_max_objective;
    std::copy(position, position+count, pos);
  }
}

void Particle::report() const
{
  return;
  double v_norm = 0.0;
  for ( int i = 0 ; i < count ; ++i ) {
    std::cerr << (int) (0.5 + position[i]) << " ";
    v_norm += velocity[i] * velocity[i];
  }
  v_norm = std::sqrt(v_norm);
  std::cerr << local_max_objective << " " << v_norm << "\n";
}
