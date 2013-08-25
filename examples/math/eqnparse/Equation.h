# if ! defined( Equation_h )
#define Equation_h 1

#include "../newton/ParameterSpace.h"

class Equation
{
public:
  Equation();
  virtual ~Equation();

  virtual double eval_fx( ParameterSpace const & parms ) const = 0;
  virtual double eval_dx( ParameterSpace const & parms ) const;
  virtual Equation * clone() const = 0;
  virtual bool isConstant() const = 0;
  virtual Equation * derive() const = 0;
  virtual void display(bool parens) const = 0;

private:
  mutable Equation * derivative;
};

class Exponential : public Equation
{
public:
  Exponential( double coeff, Equation * exp );
  ~Exponential();

  virtual double eval_fx( ParameterSpace const & parms ) const;
  virtual Equation * clone() const;
  virtual bool isConstant() const;
  virtual Equation * derive() const;
  virtual void display(bool parens) const;

private:
  double     coefficient;
  Equation * exponent;
};

class PowerFunction : public Equation
{
public:
  PowerFunction( double coeff, double exp, size_t var );

  virtual double eval_fx( ParameterSpace const & parms ) const;
  virtual Equation * clone() const;
  virtual bool isConstant() const;
  virtual Equation * derive() const;
  virtual void display(bool parens) const;

private:
  double coefficient;
  double exponent;
  size_t whichvar;
};

class BinaryFunction : public Equation
{
public:
  BinaryFunction( Equation * arg1, Equation * arg2, char op );
  ~BinaryFunction();

  virtual double eval_fx( ParameterSpace const & parms ) const;
  virtual Equation * clone() const;
  virtual bool isConstant() const;
  virtual Equation * derive() const;
  virtual void display(bool parens) const;

private:
  Equation * argument1;
  Equation * argument2;
  char       operation;
};

class Constant : public Equation
{
public:
  Constant( double val );

  virtual double eval_fx( ParameterSpace const & parms ) const;
  virtual double eval_dx( ParameterSpace const & parms ) const;
  virtual Equation * clone() const;
  virtual bool isConstant() const;
  virtual Equation * derive() const;
  virtual void display(bool parens) const;

private:
  double value;
};

class Zero : public Constant
{
public:
  Zero();
};

#endif
