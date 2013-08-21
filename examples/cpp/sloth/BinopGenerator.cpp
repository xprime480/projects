
#include <sstream>

#include "FormFactory.h"

#include "BinopGenerator.h"

using namespace std;
using namespace Sloth;

namespace {
  set<string> getArithSet()
  {
    static char const * opsRaw[] = {
      "+", "-", "*", "/", "%"
    };
    static size_t const nOps = sizeof(opsRaw) / sizeof (opsRaw[0]);
    static set<string> ops(opsRaw, opsRaw + nOps);

    return ops;
  }

  set<string> getCompareSet()
  {
    static char const * opsRaw[] = {
      "<", "<=", ">", ">=", "==", "!="
    };
    static size_t const nOps = sizeof(opsRaw) / sizeof (opsRaw[0]);
    static set<string> ops(opsRaw, opsRaw + nOps);

    return ops;
  }

  set<string> getAllOps()
  {
    set<string> ops;
    set<string> temp;

    temp = getArithSet();
    ops.insert(temp.begin(), temp.end());

    temp = getCompareSet();
    ops.insert(temp.begin(), temp.end());

    return ops;
  }
}

BinopGenerator::BinopGenerator(std::string const & _op,
			       Form const & _arg1,
			       Form const & _arg2)
  : op(_op)
  , arg1(_arg1)
  , arg2(_arg2)
{
  int test = 0;
  test |= arg1.isSequence() ? 2 : 0;
  test |= arg2.isSequence() ? 1 : 0;

  switch ( test ) {
  case 0: type = BinopArgs_NonNon; break;
  case 1: type = BinopArgs_NonSeq; break;
  case 2: type = BinopArgs_SeqNon; break;
  case 3: type = BinopArgs_SeqSeq; break;
  default: type = BinopArgs_Unknown; break;
  }
}

set<string> BinopGenerator::getBinopSet()
{
  static set<string> ops(getAllOps());
  return ops;
}


bool BinopGenerator::isNil() const
{
  bool rv = type == BinopArgs_Unknown;

  if ( type == BinopArgs_SeqSeq || type == BinopArgs_SeqNon ) {
    rv |= arg1.isNil();
  }
  if ( type == BinopArgs_SeqSeq || type == BinopArgs_NonSeq ) {
    rv |= arg2.isNil();
  }

  return rv;
}

Form BinopGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  switch ( type ) { 
  case BinopArgs_Unknown:
    {
      stringstream s;
      s << "Unknown argument types to operator '";
      s << op;
      s << "':  (<";
      s << arg1.toString();
      s << ">, <";
      s << arg2.toString();
      s << ">)";
      return FormFactory::makeMessage(s.str());
    }
    break;

  case BinopArgs_SeqSeq:
    return eval(arg1.getHead(), arg2.getHead());
    break;

  case BinopArgs_SeqNon:
    return eval(arg1.getHead(), arg2);
    break;
	  
  case BinopArgs_NonSeq:
    return eval(arg1, arg2.getHead());
    break;

  case BinopArgs_NonNon:
    return eval(arg1, arg2);
    break;

  default:
    break;
  }

  stringstream s;
  s << "Internal error at " << __FILE__ << ", " << __LINE__;
  return FormFactory::makeMessage(s.str());
}

Form BinopGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  BinopGenerator * gen(0);

  switch ( type ) { 
  case BinopArgs_Unknown:
    return FormFactory::makeNil();
    break;
    
  case BinopArgs_SeqSeq:
    gen = new BinopGenerator(op, arg1.getTail(), arg2.getTail());
    break;

  case BinopArgs_SeqNon:
    gen = new BinopGenerator(op, arg1.getTail(), arg2);
    break;
	  
  case BinopArgs_NonSeq:
    gen = new BinopGenerator(op, arg1,           arg2.getTail());
    break;

  case BinopArgs_NonNon:
    return FormFactory::makeNil();
    break;

  default:
    {
      stringstream s;
      s << "Internal error at " << __FILE__ << ", " << __LINE__;
      return FormFactory::makeMessage(s.str());
    }
    break;
  }
  
  return FormFactory::makeSequence(gen);
}

string BinopGenerator::toString() const
{
  stringstream s;
  s << "(" << op << " " << arg1.toString() << " " << arg2.toString() << ")";
  return s.str();
}

Form BinopGenerator::eval(Form const & a1, Form const & a2) const
{
  static set<string> arith   = getArithSet();
  static set<string> compare = getCompareSet();

  if ( arith.find(op) != arith.end() ) {
    return evalArith(a1, a2);
  }
  if ( compare.find(op) != compare.end() ) {
    return evalCompare(a1, a2);
  }

  stringstream s;
  s << "Unknown binary operator: '" << op << "'";
  return FormFactory::makeMessage(s.str());
}

Form BinopGenerator::evalArith(Form const & a1, Form const & a2) const
{
  string const msg = "Exepected integer form, got: ";
  stringstream s;

  if ( ! a1.hasIntValue() ) {
    s << msg << "'" << a1.toString() << "'";
    return FormFactory::makeMessage(s.str());
  }
  if ( ! a2.hasIntValue() ) {
    s << msg << "'" << a2.toString() << "'";
    return FormFactory::makeMessage(s.str());
  }

  int i1 = a1.getIntValue();
  int i2 = a2.getIntValue();
  int rv = -1;

  if ( op == "+" ) {
    rv = i1 + i2;
  }
  else if ( op == "-" ) {
    rv = i1 - i2;
  }
  else if ( op == "*" ) {
    rv = i1 * i2;
  }
  else if ( op == "/" ) {
    if ( 0 == i2 ) {
      return FormFactory::makeMessage("Division by zero");
    }
    rv = i1 / i2;
  }
  else if ( op == "%" ) {
    if ( 0 == i2 ) {
      return FormFactory::makeMessage("Modulus by zero");
    }
    rv = i1 % i2;
  }
  else {
    s << "Internal error at " << __FILE__ << " " << __LINE__;
    return FormFactory::makeMessage(s.str());
  }

  return FormFactory::makeInt(rv);
}

Form BinopGenerator::evalCompare(Form const & a1, Form const & a2) const
{
  string const msg1 = "Exepected two forms of the same type, got: ";
  string const msg2 = "Unknown form type: ";
  stringstream s;

  Form::FormType t1 = a1.getType();
  Form::FormType t2 = a2.getType();
  if ( t1 != t2 ) {
    s << msg1 << "'" << a1.toString() << "', '" << a2.toString() << "' (operator '" << op << "')";
    return FormFactory::makeMessage(s.str());
  }


  switch ( t1 ) {
  case Form::FormType_INTEGER:
    return evalCompareInt(a1, a2);
    break;

  case Form::FormType_BOOLEAN:
    return evalCompareBoolean(a1, a2);
    break;

  case Form::FormType_STRING:
    return evalCompareString(a1, a2);
    break;

  case Form::FormType_SEQUENCE:
    return evalCompareSequence(a1, a2);
    break;

  case Form::FormType_SYMBOL:
    return evalCompareSymbol(a1, a2);
    break;

  case Form::FormType_MESSAGE:
    return evalCompareMessage(a1, a2);
    break;

  case Form::FormType_BLOB:
    return evalCompareBlob(a1, a2);
    break;

  default:
    {
      s << msg1 << "'" << a1.toString() << "', '" << a2.toString() << "' (operator '" << op << "')";
      return FormFactory::makeMessage(s.str());
    }
    break;
  };

  s << "Internal error at " << __FILE__ << " " << __LINE__;
  return FormFactory::makeMessage(s.str());
}

Form BinopGenerator::evalCompareInt(Form const & a1, Form const & a2) const
{
  int value1 = a1.getIntValue();
  int value2 = a2.getIntValue();

  bool rv = false;

  if ( op == "<" ) {
    rv = value1 < value2;
  }
  else if ( op == "<=" ) {
    rv = value1 <= value2;
  }
  else if ( op == ">" ) {
    rv = value1 > value2;
  }
  else if ( op == ">=" ) {
    rv = value1 >= value2;
  }
  else if ( op == "==" ) {
    rv = value1 == value2;
  }
  else if ( op == "!=" ) {
    rv = value1 != value2;
  }
  else {
    stringstream s;
    s << "Internal error at " << __FILE__ << " " << __LINE__;
    return FormFactory::makeMessage(s.str());
  }

  return FormFactory::makeBoolean(rv);
}  

Form BinopGenerator::evalCompareBoolean(Form const & a1, Form const & a2) const
{
  bool value1 = a1.getBooleanValue();
  bool value2 = a2.getBooleanValue();

  bool rv = false;

  if ( op == "==" ) {
    rv = value1 == value2;
  }
  else if ( op == "!=" ) {
    rv = value1 != value2;
  }
  else {
    stringstream s;
    s << "Operator not supported for booleans: '" << op << "'";
    return FormFactory::makeMessage(s.str());
  }

  return FormFactory::makeBoolean(rv);
}

Form BinopGenerator::evalCompareString(Form const & a1, Form const & a2) const
{
  string value1 = a1.getStringValue();
  string value2 = a2.getStringValue();

  bool rv = false;
  int compare = value1.compare(value2);

  if ( op == "<" ) {
    rv = compare < 0;
  }
  else if ( op == "<=" ) {
    rv = compare < 1;
  }
  else if ( op == ">" ) {
    rv = compare > 0;
  }
  else if ( op == ">=" ) {
    rv = compare > -1;
  }
  else if ( op == "==" ) {
    rv = compare == 0;
  }
  else if ( op == "!=" ) {
    rv = compare != 0;
  }
  else {
    stringstream s;
    s << "Internal error at " << __FILE__ << " " << __LINE__;
    return FormFactory::makeMessage(s.str());
  }

  return FormFactory::makeBoolean(rv);
}

Form BinopGenerator::evalCompareSequence(Form const & a1, Form const & a2) const
{
  return FormFactory::makeMessage("Sequence comparison not implemented");
}

Form BinopGenerator::evalCompareSymbol(Form const & a1, Form const & a2) const
{
  return FormFactory::makeMessage("Symbol comparison not implemented");
}

Form BinopGenerator::evalCompareMessage(Form const & a1, Form const & a2) const
{
  return evalCompareString(a1, a2);
}

Form BinopGenerator::evalCompareBlob(Form const & a1, Form const & a2) const
{
  void * value1 = a1.getBlobValue();
  void * value2 = a2.getBlobValue();

  bool rv = false;

  if ( op == "==" ) {
    rv = value1 == value2;
  }
  else if ( op == "!=" ) {
    rv = value1 != value2;
  }
  else {
    stringstream s;
    s << "Operator not supported for blobs: '" << op << "'";
    return FormFactory::makeMessage(s.str());
  }

  return FormFactory::makeBoolean(rv);
}
