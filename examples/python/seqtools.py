#!/usr/bin/env python3

"""
functions for creating sequences from other sequences

Note: Many of these can be better implemented by functions from the 
      itertools library.
"""

def chunker(seq, n) :
    """Create a new sequence of N sized chunks of SEQ.

    SEQ is any iterable.
    N   is the number of items to pull from SEQ for each chunk.
    """
    s = iter(seq)
    more = True
    while more :
        v = []
        for i in range(n) :
            try :
                v.append(s.next())
            except StopIteration :
                more = False
                break

        if len(v) == 0 :
            return
        yield iter(v)

    return

def agg_seq(seq, n, agg) :
    """Create a new sequence by applying AGG to N-sized chunks of SEQ.
    
    SEQ is any iterable.
    N   is the number of items to pull from SEQ for each chunk.
    AGG is any callable which will take an element of SEQ.
    """


    for x in chunker(seq, n) :
        yield agg(x)

def flatten(seqs) :
    """Transform a sequence of sequences it into a flat sequence.

    SEQS is any sequence of sequences.
    """
    while True :
        for e in seqs :
            if type(e) in (tuple,list) :
                for i in flatten(e) :
                    yield i
            else :
                yield e
            
    return
    
def bestof(seq,n,k) :
    """Sort chunks of a sequence and return a subset of each chunk.

    SEQ is any iterable.
    N   is the number of items to pull from SEQ for each chunk.
    K   is the number of items to return from each chunk.

    Each chunk of N items is sorted and the largest (by the sort)
    K items are returned.
    """
    for s in chunker(seq, k) :
        for x in sorted(s)[-n:] :
            yield x

