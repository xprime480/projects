
#include <iostream>
#include <cmath>

#include "Equation.h"

Equation::Equation()
  : derivative( 0 )
{
}

Equation::~Equation()
{
  delete derivative;
  derivative = 0;
}

double Equation::eval_dx( ParameterSpace const & parms ) const
{
  if ( ! derivative ) {
    derivative = derive();
  }
  return derivative->eval_fx( parms );
}




Exponential::Exponential( double coeff, Equation * exp )
  : Equation()
  , coefficient( coeff )
  , exponent( exp )
{
  if ( ! exponent ) {
    throw "Bad exponent in Exponential constructor";
  }
}

Exponential::~Exponential()
{
  delete exponent;
  exponent = 0;
}

double Exponential::eval_fx( ParameterSpace const & parms ) const
{
  return coefficient * std::exp( exponent->eval_fx( parms ) );
}

Equation * Exponential::clone() const
{
  return new Exponential( coefficient, exponent->clone() );
}

bool Exponential::isConstant() const
{
  return exponent->isConstant();
}

Equation * Exponential::derive() const
{
  Equation * t = exponent->derive();
  return new BinaryFunction( t, this->clone(), '*' );
}

void Exponential::display(bool parens) const
{
  if ( parens ) {
  std::cout << "(";
  }
  if ( coefficient != 1.0 ) {
    std::cout << coefficient << " ";
  }
  std::cout << "exp(";
  exponent->display( false );
  std::cout << ")";
  if ( parens ) {
  std::cout << ")";
  }
}



PowerFunction::PowerFunction( double coeff, double exp, size_t var )
  : Equation()
  , coefficient( coeff )
  , exponent( exp )
  , whichvar( var )
{
}

double PowerFunction::eval_fx( ParameterSpace const & parms ) const
{
  return coefficient * std::pow( parms[ whichvar ], exponent );
}

Equation * PowerFunction::clone() const
{
  return new PowerFunction( coefficient, exponent, whichvar );
}

bool PowerFunction::isConstant() const
{
  return 0 == coefficient || 0 == exponent;
}

Equation * PowerFunction::derive() const
{
  if ( 1.0 == exponent ) {
    return new Constant( coefficient );
  }

  double c = coefficient * exponent;
  return new PowerFunction( c, exponent - 1.0, whichvar );
}

void PowerFunction::display(bool parens) const
{
  if ( coefficient != 1.0 ) {
    std::cout << coefficient << " ";
  }
  std::cout << ("xyzwtuv"[whichvar]);
  if ( exponent != 1.0 ) {
    std::cout << "^" << exponent;
  }
}




BinaryFunction::BinaryFunction( Equation * arg1, Equation * arg2, char op )
  : Equation()
  , argument1( arg1 )
  , argument2( arg2 )
  , operation( op )
{
  if ( ! arg1 || ! arg2 ) {
    throw "Bad argument in BinaryFunction constructor";
  }
}

BinaryFunction::~BinaryFunction()
{
  delete argument1;
  delete argument2;
  argument1 = argument2 = 0;
}

double BinaryFunction::eval_fx( ParameterSpace const & parms ) const
{
  double arg1 = argument1->eval_fx( parms );
  double arg2 = argument2->eval_fx( parms );
  double value;

  switch ( operation ) {
  case '+' :
    value = arg1 + arg2;
    break;
  case '-' :
    value = arg1 - arg2;
    break;
  case '*' :
    value = arg1 * arg2;
    break;
  case '/' :
    if ( std::abs( arg2 ) < 1e-12 ) {
      throw "division by zero";
    }
    value = arg1 / arg2;
    break;
  case '^' :
    value = std::pow( arg1, arg2 );
    break;
  default :
    throw "unknown operator";
    break;
  }

  return value;
}

Equation * BinaryFunction::clone() const
{
  return new BinaryFunction( argument1->clone(), 
			     argument2->clone(), 
			     operation );
}

bool BinaryFunction::isConstant() const
{
  return argument1->isConstant() && argument2->isConstant();
}

Equation * BinaryFunction::derive() const
{
  Equation * t1;
  Equation * t2;
  Equation * t3;
  Equation * t4;
    
  switch ( operation ) {
  case '+' :
  case '-' :
    return new BinaryFunction( argument1->derive(), 
			       argument2->derive(), 
			       operation );
    break;

  case '*' :
    t1 = new BinaryFunction( argument1->derive(), argument2->clone(), '*' );
    t2 = new BinaryFunction( argument1->clone(), argument2->derive(), '*' );
    return new BinaryFunction( t1, t2, '+' );
    break;

  case '/' :
    t3 = new BinaryFunction( argument1->derive(), argument2->clone(), '*' );
    t4 = new BinaryFunction( argument1->clone(), argument2->derive(), '*' );
    t1 = new BinaryFunction( t3, t4, '-' );
    t2 = new BinaryFunction( argument2->clone(), new Constant( 2.0 ), '^' );
    return new BinaryFunction( t1, t2, '/' );
    break;

  case '^' :
    if ( argument1->isConstant() ) {
      return new Zero();
    }
    else if ( argument2->isConstant() ) {
      ParameterSpace p(0);
      t1 = argument2->clone();
      t2 = argument1->clone();
      t3 = new Constant( argument2->eval_fx( p ) - 1.0 );
      t4 = argument1->derive();
      return new BinaryFunction( new BinaryFunction( t1, 
						     new BinaryFunction( t2, 
									 t3,
									 '^' ),
						     '*'),
				 t4,
				 '*' );
    }
    else {
      throw "cannot differentiate expression";
    }
    break;

  default :
    throw "unknown operator";
    break;
  }

  return 0;
}

void BinaryFunction::display(bool parens) const
{
  if ( parens ) {
    std::cout << "(";
  }
  argument1->display( true );
  std::cout << operation;
  argument2->display( true );
  if ( parens ) {
    std::cout << ")";
  }
}



Constant::Constant( double val )
  : Equation()
  , value( val )
{
}

double Constant::eval_fx( ParameterSpace const & parms ) const
{
  return value;
}

double Constant::eval_dx( ParameterSpace const & parms ) const
{
  return 0.0;
}

Equation * Constant::clone() const
{
  return new Constant( value );
}

bool Constant::isConstant() const
{
  return true;
}

Equation * Constant::derive() const
{
  return new Zero();
}

void Constant::display(bool parens) const
{
  std::cout << value;
}



Zero::Zero()
  : Constant( 0.0 )
{
}
