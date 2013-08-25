#if ! defined( Function_h )
#define Function_h 1

#include "ParameterSpace.h"

class Function
{
public:
  typedef ParameterSpace parameter_space_type;

  virtual double
  eval         ( parameter_space_type const & parms ) const = 0;

  virtual double
  eval_1st_derv( parameter_space_type const & parms ) const = 0;

  virtual double
  eval_2nd_derv( parameter_space_type const & parms ) const = 0;
};

#endif
