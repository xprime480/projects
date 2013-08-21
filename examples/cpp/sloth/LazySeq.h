#if ! defined(LazySeq_h)
#define LazySeq_h 1

#include <cstdlib>

/**
 * Main class and miscellaneous items for LazySequences
 */

extern bool gDebug;		// true for extra debugging

#if 1

#include <iostream>

/**
 * Macro to trace allocations of Lazy Sequences
 */
#define TRACEALLOC(p)  \
  if ( gDebug ) { \
    std::cerr << "new @ line " << __LINE__ << " " << (p) << std::endl; \
  }

/**
 * Macro to trace deallocations of Lazy Sequences
 */
#define TRACEFREE(p)   \
  if ( gDebug ) { \
    std::cerr << "delete " << (p) << std::endl; \
  }

#else

#define TRACEALLOC(p)
#define TRACEFREE(p)


#endif

/**
 * LazySeqStat
 *
 * Base class of all lazy sequences.  Lazy sequences are references
 * counted, but the client must handle all incrementing and
 * decrementing of references.
 */
class LazySeqStat
{
public:
  /**
   * constructor
   */
  LazySeqStat();

  /**
   * destructor
   */
  virtual ~LazySeqStat();

  /**
   * report on the number of allocations and frees since program startup.
   */
  static void report();

  /**
   * addref
   *
   * Increment the reference count for an object.
   *
   * @param seq a lazy sequence object.
   */
  static void addref(LazySeqStat * seq);

  /**
   * deref
   *
   * Decrement the reference count for an object, freeing it when the
   * count gets to zero.
   *
   * @param seq a lazy sequence object.
   */
  static void deref(LazySeqStat * seq);

private:
  static size_t allocs;		// number of LazySeqStat objects allocated
  static size_t frees;		// number of LazySeqStat objects freed
  static size_t maxallocs;	// maximum value of  allocs - frees
				// over time.

  size_t refs;			// number of references to this object.
};

/**
 * LazySeq a lazy sequence over some type.  A lazy sequence has the
 * property that only the head is realized, and the rest of the
 * sequence (potentially infinite) is only created on demand.
 *
 * The head item of a lazy sequence with the empty property == true
 * should not be relied upon.
 */
template <typename T = int>
class LazySeq : public LazySeqStat
{
public:
  /**
   * default constructor
   *
   * Create an empty lazy sequence with an uninitialized head
   */
  LazySeq()
    : LazySeqStat()
    , empty(true)
  {
    ++allocs;
  }

  /**
   * constructor
   *
   * create an initialized lazy sequence
   *
   * @param v the head of the sequence
   * @param e true iff the sequence is empty
   */
  LazySeq(T v, bool e)
    : head(v)
    , empty(e)
  {
    ++allocs;
    if ( ( allocs - frees ) > maxallocs ) {
      maxallocs = allocs - frees;
    }
  }

  /**
   * destructor
   */
  virtual ~LazySeq()
  {
    ++frees;
  }

  T  head;			// first item of non-empty sequence
  bool empty;			// true iff sequence is empty

  /**
   * tail
   *
   * Compute the next item in the sequence and return a pointer to the
   * new lazy sequence.
   *
   * @return A lazy sequence.
   */
  virtual LazySeq<T> * tail() = 0;

  /**
   * cdr
   *
   * Get the tail of a sequence with some book-keeping.  The original
   * sequence will be deref'ed once, possibly freeing it.
   *
   * @param seq a lazy sequence
   *
   * @return a new lazy sequence whose refcount is at least one.
   */
  static LazySeq<T> * cdr(LazySeq<T> * seq)
  {
    if ( seq ) {
      LazySeq * next = seq->tail();
      addref(next);
      deref(seq);
      seq = next;
    }

    return seq;
  }

private:
};

#include "NullSeq.h"

#endif // not defined LazySeq_h
