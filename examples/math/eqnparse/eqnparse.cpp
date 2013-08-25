
#include <iostream>
#include <sstream>

#include "Equation.h"
#include "Parser.h"

struct Range
{
  Range( double l, double h, double s )
    : low( l )
    , high( h )
    , step( s )
  {
  }

  double low;
  double high;
  double step;
};

typedef std::vector< Range > ParameterRange;

void gridtest( Equation * eqn, ParameterRange const & grid )
{
  if ( grid.empty() ) {
    std::cout << "no parameters\n";
    return;
  }
  if ( ! eqn ) {
    std::cout << "no equation\n";
    return;
  }

  std::cout << "f(x) = ";  eqn->display( false ); std::cout << "\n";

  Range const & r = grid.front();
  ParameterSpace ps(1);
  for ( double x = r.low ; x <= r.high ; x += r.step ) {
    ps[0] = x;
    double y = eqn->eval_fx( ps );
    double d = eqn->eval_dx( ps );
    std::cout << "x = " << x
	      << " => f(x) = " << y
	      << " f'(x) =  " << d << "\n";
  }
}

void fntest001()
{
  std::cout << "\n";
  std::cout << "f(x) = 0\n";
  Equation * eqn = new Zero();
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest002()
{
  std::cout << "\n";
  std::cout << "f(x) = 3.75\n";
  Equation * eqn = new Constant( 3.75 );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest003()
{
  std::cout << "\n";
  std::cout << "f(x) = 2 x^2\n";
  Equation * eqn = new PowerFunction( 2, 2, 0 );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest004()
{
  std::cout << "\n";
  std::cout << "f(x) = fourth root (x)\n";
  Equation * eqn = new PowerFunction( 1.0, 0.25, 0 );
  Range r( 0, 16, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest005()
{
  std::cout << "\n";
  std::cout << "f(x) = exp(x)\n";
  Equation * t   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * eqn = new Exponential( 1.0, t );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest006()
{
  std::cout << "\n";
  std::cout << "f(x) = exp(3.333)\n";
  Equation * t   = new Constant( 3.333 );
  Equation * eqn = new Exponential( 1.0, t );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest007()
{
  std::cout << "\n";
  std::cout << "f(x) = x+2\n";
  Equation * t   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * u   = new Constant( 2.0 );
  Equation * eqn = new BinaryFunction( t, u, '+' );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest008()
{
  std::cout << "\n";
  std::cout << "f(x) = x-2\n";
  Equation * t   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * u   = new Constant( 2.0 );
  Equation * eqn = new BinaryFunction( t, u, '-' );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest009()
{
  std::cout << "\n";
  std::cout << "f(x) = 2x\n";
  Equation * t   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * u   = new Constant( 2.0 );
  Equation * eqn = new BinaryFunction( t, u, '*' );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest010()
{
  std::cout << "\n";
  std::cout << "f(x) = x/2\n";
  Equation * t   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * u   = new Constant( 2.0 );
  Equation * eqn = new BinaryFunction( t, u, '/' );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest011()
{
  std::cout << "\n";
  std::cout << "f(x) = x^2\n";
  Equation * t   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * u   = new Constant( 2.0 );
  Equation * eqn = new BinaryFunction( t, u, '^' );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest012()
{
  std::cout << "\n";
  std::cout << "f(x) = (x+1)(x-1)\n";
  Equation * a   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * b   = a->clone();
  Equation * c   = new Constant( 1.0 );
  Equation * d   = c->clone();
  Equation * e   = new BinaryFunction( a, c, '+' );
  Equation * f   = new BinaryFunction( b, d, '-' );
  Equation * eqn = new BinaryFunction( e, f, '*' );
  Range r( -10, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void fntest013()
{
  std::cout << "\n";
  std::cout << "f(x) = 1/x\n";
  Equation * a   = new PowerFunction( 1.0, 1.0, 0 );
  Equation * c   = new Constant( 1.0 );
  Equation * eqn = new BinaryFunction( c, a, '/' );
  Range r( 1, 10, 1 );
  ParameterRange pr;
  pr.push_back( r );
  gridtest( eqn, pr );
  delete eqn;
}

void functiontests()
{
  fntest001();
  fntest002();
  fntest003();
  fntest004();
  fntest005();
  fntest006();
  fntest007();
  fntest008();
  fntest009();
  fntest010();
  fntest011();
  fntest012();
  fntest013();
}

void parsetest( char ** argv )
{
  try {
    std::stringstream input( argv[1] );
    Equation * eqn = Parser( input ).parse();
    if ( ! eqn ) {
      std::cout << "Parsing failed\n";
      return;
    }

    double n,x,s;

    n = std::atof( argv[ 2 ] );
    x = std::atof( argv[ 3 ] );
    s = std::atof( argv[ 4 ] );

    Range r( n, x, s );
    ParameterRange pr;
    pr.push_back( r );
    gridtest( eqn, pr );

    delete eqn;
  }
  catch ( char const * e ) {
    std::cout << "Error: " << e << "\n";
  }
  catch ( ... ) {
    std::cout << "Other error\n";
  }
}

int main( int argc, char ** argv )
{
  if ( argc > 4 ) {
    parsetest( argv );
  }
  else {
    functiontests();
  }
  return 0;
}
