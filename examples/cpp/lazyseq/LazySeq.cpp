#include <iostream>

#include "LazySeq.h"

using namespace std;

bool gDebug = false;		// true for extra debugging

size_t LazySeqStat::allocs    = 0;
size_t LazySeqStat::frees     = 0;
size_t LazySeqStat::maxallocs = 0;

LazySeqStat::LazySeqStat()
  : refs(0)
{
  ++allocs;
  if ( ( allocs - frees ) > maxallocs ) {
    maxallocs = allocs - frees;
  }
}


LazySeqStat::~LazySeqStat()
{
  ++frees;
}

void LazySeqStat::report()
{
  cout << allocs << " allocations; "
       << frees << " frees; "
       << maxallocs << " max live allocs"
       << endl;
}

void LazySeqStat::addref(LazySeqStat * seq)
{
  if ( seq ) {
    ++seq->refs;
  }
}

void LazySeqStat::deref(LazySeqStat * seq)
{
  if ( seq ) {
    if ( seq->refs == 0 ) {
      cerr << "Too many derefs" << endl;
    }
    --seq->refs;
  }

  if ( seq->refs == 0  ) {
    TRACEFREE(seq);
    delete seq;
  }
}
