
#include <iostream>

#include "LazyForm.h"

#include "LazySeqUtils.h"

using namespace std;
using namespace lazy;

LazyForm::~LazyForm()
{
}

LazyErrorForm::LazyErrorForm(std::string const & _m)
  : LazyForm()
  , message(_m)
{
}

void LazyErrorForm::print()
{
  cout << message << endl;
}

LazyIntStream::LazyIntStream(LazySeq<int> * _seq)
  : LazyForm()
  , seq(_seq) 
{
  LazySeqStat::addref(seq);
}

LazyIntStream::~LazyIntStream()
{
  LazySeqStat::deref(seq);
}

void LazyIntStream::print()
{
  LazySeqUtils<int>::print(seq);
}

LazySeq<int> * LazyIntStream::getSequence()
{
  return seq;
}

