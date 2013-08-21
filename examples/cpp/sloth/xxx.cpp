/*******************************************************************
 *
 * Implementation for BinopFormImpl
 *
 *******************************************************************/

BinopFormImpl::BinopFormImpl(string const & _op,
			     Form const & _a1,
			     Form const & _a2)
  : op(_op)
  , arg1(_a1)
  , arg2(_a2)
{
}

string BinopFormImpl::toString() const
{
  stringstream s;
  s << "(" << op << " " << arg1 << " " << arg2 << ")";
  return s.str();
}

FormImpl * BinopFormImpl::eval()
{
  if ( isNil() ) {
    return NilFormImpl::getInstance();
  }

  if ( arg1.hasIntValue() && arg2.hasIntValue() ) {
    return eval(op, arg1.getIntValue(), arg2.getIntValue());
  }

  if ( arg1.hasIntValue() ) {
    SequenceGenerator * g = new Infinite(arg1);
    Form f = FormFactory::makeSequence(g);
    return eval(op, f, arg2);
  }

  if ( arg2.hasIntValue() ) {
    SequenceGenerator * g = new Infinite(arg2);
    Form f = FormFactory::makeSequence(g);
    return eval(op, arg1, f);
  }

  return eval(op, arg1, arg2);
}

bool BinopFormImpl::isNil() const
{
  return arg1.isNil() || arg2.isNil();
}

bool BinopFormImpl::hasIntValue() const
{
  Form f = eval(op, arg1.getIntValue(), arg2.getIntValue());
  return f.hasIntValue();
}

int BinopFormImpl::getIntValue() const
{
  Form f = eval(op, arg1.getIntValue(), arg2.getIntValue());
  if ( ! f.hasIntValue() ) {
    throw runtime_error(f.toString());
  }
  return f.getIntValue();
}

bool BinopFormImpl::hasBooleanValue() const
{
  Form f = eval(op, arg1.getIntValue(), arg2.getIntValue());
  return f.hasBooleanValue();
}

bool BinopFormImpl::getBooleanValue() const
{
  Form f = eval(op, arg1.getIntValue(), arg2.getIntValue());
  if ( ! f.hasIntValue() ) {
    throw runtime_error(f.toString());
  }
  return f.getBooleanValue();
}

bool BinopFormImpl::isSequence() const
{
  bool s1 = arg1.isSequence();
  bool s2 = arg2.isSequence();
  bool i1 = arg1.hasIntValue();
  bool i2 = arg2.hasIntValue();

  // at least one is a sequence and the other a sequence or integer

  return ( ( s1 && s1 ) || ( s1 && i2 ) || ( i1 && s2 ) );
}

Form BinopFormImpl::getHead() const
{
  Form result;

  Form a1 = headValue(arg1);
  Form a2 = headValue(arg2);
  if ( ! (a1.hasIntValue() && a2.hasIntValue()) ) {
    stringstream s;
    s << "Expected integers or streams for '" << op << "'"
      << "; got <" << arg1 << "> and <" << arg2 << ">";
    result = FormFactory::makeMessage(s.str());
  }
  else {
    result = eval(op, a1.getIntValue(), a2.getIntValue());
  }

  return result;
}

Form BinopFormImpl::getTail() const
{
  Form result;
  if ( arg1.hasIntValue() && arg2.hasIntValue() ) {
    result = FormFactory::makeNil();
  }
  else if ( arg1.isSequence() && arg2.isSequence() ) {
    result = FormFactory::makeBinop(op, arg1.getTail(), arg2.getTail());
  }
  else if ( arg1.hasIntValue() && arg2.isSequence() ) {
    result = FormFactory::makeBinop(op, arg1, arg2.getHead());
  }
  else if ( arg1.isSequence() && arg2.hasIntValue() ) {
    result = FormFactory::makeBinop(op, arg1.getHead(), arg2);
  }
  else {
    result = FormFactory::makeNil();
  }

  return result;
}

FormImpl * BinopFormImpl::eval(string const & op, int arg1, int arg2)


FormImpl * BinopFormImpl::eval(string const & op,
			       Form const & arg1,
			       Form const & arg2)
{
  static string const error1 = "BinopFormImpl::eval expecting sequence, got ";
  static string const error2 = "BinopFormImpl::eval expecting integer, got ";
  stringstream s;

  if ( ! arg1.isSequence() ) {
    s << error1 << arg1.toString();
    return new MessageFormImpl(s.str());
  }
  if ( ! arg2.isSequence() ) {
    s << error1 << arg2.toString();
    return new MessageFormImpl(s.str());
  }

  vector<int> values;

  Form a1 = arg1;
  Form a2 = arg2;
  while ( true ) {
    if ( a1.isNil() || a2.isNil() ) {
      break;
    }

    Form h1 = a1.getHead();
    Form h2 = a2.getHead();

    if ( ! h1.hasIntValue() ) { 
      s << error2 << h1.toString();
      return new MessageFormImpl(s.str());
    }
    if ( ! h2.hasIntValue() ) {
      s << error2 << h2.toString();
      return new MessageFormImpl(s.str());
    }

    FormImpl * fi = eval(op, h1.getIntValue(), h2.getIntValue());
    if ( ! fi->hasIntValue() ) {
      return fi;
    }

    values.push_back(fi->getIntValue());

    a1 = a1.getTail();
    a2 = a2.getTail();
  }

  vector<int> * tval = new vector<int>(values);
  Form blob = FormFactory::makeBlob(tval, deleter<vector<int> >);
  return new SequenceFormImpl(new FixedSequenceGenerator(blob));
}

Form BinopFormImpl::headValue(Form f)
{
  while ( true ) {
    if ( f.hasIntValue() ) {
      break;
    }
    if ( ! f.isSequence() ) {
      break;
    }
    if ( f.isNil() ) {
      break;
    }

    f = f.getHead();
  }

  return f;
}


/*******************************************************************
 *
 * Implementation for UnopFormImpl
 *
 *******************************************************************/

UnopFormImpl::UnopFormImpl(string const & _op, Form const & _arg)
  : op(_op)
  , arg(_arg)
{
}

string UnopFormImpl::toString() const
{
  stringstream s;
  s << "(" << op << " " << arg << ")";
  return s.str();
}

FormImpl * UnopFormImpl::eval()
{
  if ( isNil() ) {
    return NilFormImpl::getInstance();
  }

  if ( arg.hasIntValue() ) {
    return eval(op, arg.getIntValue());
  }

  return eval(op, arg);
}

bool UnopFormImpl::isNil() const
{
  return arg.isNil();
}

bool UnopFormImpl::hasIntValue() const
{
  Form f = eval(op, arg);
  return f.hasIntValue();
}

int UnopFormImpl::getIntValue() const
{
  Form f = eval(op, arg);
  if ( ! f.hasIntValue() ) {
    throw runtime_error(f.toString());
  }
  return f.getIntValue();
}

bool UnopFormImpl::hasBooleanValue() const
{
  Form f = eval(op, arg);
  return f.hasBooleanValue();
}

bool UnopFormImpl::getBooleanValue() const
{
  Form f = eval(op, arg);
  if ( ! f.hasBooleanValue() ) {
    throw runtime_error(f.toString());
  }
  return f.getBooleanValue();
}

bool UnopFormImpl::isSequence() const
{
  return arg.isSequence();
}

Form UnopFormImpl::getHead() const
{
  Form result;

  Form a = headValue(arg);
  if ( ! a.hasIntValue() ) {
    stringstream s;
    s << "Expected integers or streams for '" << op << "'"
      << "; got <" << arg << ">";
    result = FormFactory::makeMessage(s.str());
  }
  else {
    result = eval(op, a.getIntValue());
  }

  return result;
}

Form UnopFormImpl::getTail() const
{
  Form result;
  if ( arg.hasIntValue() ) {
    result = FormFactory::makeNil();
  }
  else if ( arg.isSequence() ) {
    result = FormFactory::makeUnop(op, arg.getTail());
  }
  else {
    result = FormFactory::makeNil();
  }

  return result;
}

FormImpl * UnopFormImpl::eval(string const & op, int arg)
{
  int rv = -1;
  int bv = false;
  bool isInt = true;

  if ( op == "!" ) {
    bv = ! arg;
    isInt = false;
  }
  else {
    stringstream s;
    s << "Unknown binary operator: '" << op << "'";
    return new MessageFormImpl(s.str());
  }

  return isInt 
    ? (FormImpl *) new IntFormImpl(rv)
    : (FormImpl *) BooleanFormImpl::getInstance(bv) ;
}

FormImpl * UnopFormImpl::eval(string const & op, Form const & arg)
{
  static string const error1 = "UnopFormImpl::eval expecting sequence, got ";
  static string const error2 = "UnopFormImpl::eval expecting integer, got ";
  stringstream s;

  if ( ! arg.isSequence() ) {
    s << error1 << arg.toString();
    return new MessageFormImpl(s.str());
  }

  vector<int> values;

  Form a = arg;
  while ( true ) {
    if ( a.isNil() ) {
      break;
    }

    Form h = a.getHead();

    if ( ! h.hasIntValue() ) { 
      s << error2 << h.toString();
      return new MessageFormImpl(s.str());
    }

    FormImpl * fi = eval(op, h.getIntValue());
    if ( ! fi->hasIntValue() ) {
      return fi;
    }

    values.push_back(fi->getIntValue());

    a = a.getTail();
  }

  vector<int> * tval = new vector<int>(values);
  Form blob = FormFactory::makeBlob(tval, deleter<vector<int> >);
  return new SequenceFormImpl(new FixedSequenceGenerator(blob));
}

Form UnopFormImpl::headValue(Form f)
{
  while ( true ) {
    if ( f.hasIntValue() ) {
      break;
    }
    if ( ! f.isSequence() ) {
      break;
    }
    if ( f.isNil() ) {
      break;
    }

    f = f.getHead();
  }

  return f;
}

Form FormFactory::makeUnop(string const & op, Form const & arg)
{
  Form f(new UnopFormImpl(op, arg));
  return f;
}

set<string> FormFactory::getUnopSet()
{
  static char const * opsRaw[] = {
    "!"
  };
  static size_t const nOps = sizeof(opsRaw) / sizeof (opsRaw[0]);
  static set<string> ops(opsRaw, opsRaw + nOps);

  return ops;
}

    static Form makeBinop(std::string const & op, 
			  Form const & arg1, 
			  Form const & arg2);
    static Form makeUnop(std::string const & op, Form const & arg);

    static std::set<std::string> getUnopSet();
