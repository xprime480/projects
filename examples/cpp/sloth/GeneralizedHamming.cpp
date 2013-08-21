
#include "GeneralizedHamming.h"

GeneralizedHamming::GeneralizedHamming(LazySeq<int> * gens)
  : LazySeq<int>()
  , generators(gens)
{
  init();
}

GeneralizedHamming::GeneralizedHamming(Sloth::Form const & gens)
  : LazySeq<int>()
  , generators(gens.getLazySeq())
{
  init();
}

GeneralizedHamming::~GeneralizedHamming()
{
  deref(generators);
  generators = 0;
}

LazySeq<int> * GeneralizedHamming::tail()
{
  if ( empty ) {
    LazySeq<int> * z = new NullSeq<int>();
    TRACEALLOC(z);
    return z;
  }

  LazySeq<int> * a = new Times<int>(generators->head, this);
  TRACEALLOC(a);
  LazySeq<int> * b = new GeneralizedHamming(generators->tail());
  TRACEALLOC(b);
  LazySeq<int> * z = new Merge<int>(a, b);
  TRACEALLOC(z);
  return z;
}

void GeneralizedHamming::init()
{
  addref(generators);
  if ( generators && ! generators->empty ) {
    head = generators->head;
    empty = false;
  }
}
