#include <cmath>
#include <cstdlib>

#include "Newton.h"
#include "Function.h"

class RootSolver : public Function
{
public:
  typedef Function::parameter_space_type parameter_space_type;

  RootSolver( double n, double p )
    : nn( n )
    , pow( p )
  {
  }

  virtual double
  eval         ( parameter_space_type const & parms ) const
  {
    return std::pow( parms[ 0 ], pow ) - nn;
  }

  virtual double
  eval_1st_derv( parameter_space_type const & parms ) const
  {
    return pow * std::pow( parms[ 0 ], pow - 1.0 );
  }

  virtual double
  eval_2nd_derv( parameter_space_type const & parms ) const
  {
    return pow * ( pow - 1 ) * std::pow( parms[ 0 ], pow - 2.0 );
  }

private:
  double nn;
  double pow;
};

int main( int argc, char ** argv )
{
  double r = 2;
  double p = 2;

  if ( argc > 1 ) {
    r = std::atol( argv[ 1 ] );
  }
  if ( argc > 2 ) {
    p = std::atol( argv[ 2 ] );
  }

  RootSolver     rs( r, p );
  NewtonSolver   ns( 1e-12 );
  ParameterSpace parms( 1 );
  parms[ 0 ] = 1.0;		// convienient initial guess
  if ( ns.solve( rs, parms ) ) {
    std::cerr << "x = " << parms[ 0 ] << "\n"; // answer
  }
  else {
    std::cerr << "No solution found\n";	// no answer
  }
  return 0;
}
