
#include <sstream>

#include "FormFactory.h"

#include "FixedSequenceGenerator.h"

using namespace std;
using namespace Sloth;

FixedSequenceGenerator::FixedSequenceGenerator(Form const & _b, size_t _p)
  : blob(_b)
  , pos(_p)
{
}

bool FixedSequenceGenerator::isNil() const
{
  if ( ! blob.isBlob() ) {
    return true;
  }
  
  void * b = blob.getBlobValue();
  if ( ! b ) {
    return true;
  }
  vector<int> * s = (vector<int>*)(b);

  return s->size() <= pos;
}

Form FixedSequenceGenerator::head() const
{
  if ( isNil() ) {
    return headFromNil();
  }

  vector<int> * s = (vector<int>*)(blob.getBlobValue());
  int v = s->at(pos);
  return FormFactory::makeInt(v);
}

Form FixedSequenceGenerator::tail() const
{
  if ( isNil() ) {
    return FormFactory::makeNil();
  }

  return FormFactory::makeSequence(new FixedSequenceGenerator(blob, pos+1));
}

string FixedSequenceGenerator::toString() const
{
  if ( isNil() ) {
    return FormFactory::makeNil().toString();
  }
  else {
    stringstream s;
    vector<int> * v = (vector<int>*)(blob.getBlobValue());
    s << v->at(pos);
    for ( size_t x = pos+1 ; x < v->size() ; ++x ) {
      s << " " << v->at(x);
    }
    return s.str();
  }
}
