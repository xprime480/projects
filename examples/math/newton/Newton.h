#if ! defined( Newton_h )
#define Newton_h 1

#include <iostream>
#include "Function.h"

class NewtonSolver
{
public:
  typedef Function::parameter_space_type args_type;

  NewtonSolver( double e )
    : epsilon( e )
  {
  }

  virtual bool solve( Function const & func, args_type & initial )
  {
    double & x0 = initial[ 0 ];
    for ( size_t i = 0 ; i < 100 ; ++i ) {
      double fx0  = func.eval( initial );
      double dx0 = func.eval_1st_derv( initial );
      if ( dx0 == 0 ) {
	return false;
      }
      double x1  = x0 - fx0 / dx0;
      if ( std::abs( x1 - x0 ) < epsilon ) {
	return true;
      }
      x0 = x1;
    }

    return false;
  }

private:
  double epsilon;
};

#endif
