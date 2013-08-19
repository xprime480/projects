
#include "GeneralizedHamming.h"

GeneralizedHamming::GeneralizedHamming(LazySeq<int> * gens)
  : LazySeq<int>()
  , generators(gens)
{
  addref(generators);
  if ( generators && ! generators->empty ) {
    head = generators->head;
    empty = false;
  }
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
