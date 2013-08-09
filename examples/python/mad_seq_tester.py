#!/usr/bin/env python3

"""
Create some random D&D characters using various distributions.

Warning : 1) It's not clear what this code is intended to do or how.
          2) It's not clear that seqtools functions as was originally
             intended in its version 2 form.
"""

import random
import itertools
import sys
import seqtools
import histogram

def randoms(n) :
    "generate an infinte series of integers [1..N]"
    while True :
        yield random.randrange(1, n+1)

def newStats(roller) :
    "Create a sequence of character stats from a source of random rolls"
    return seqtools.agg_seq(roller, 3, sum)

def newChars(roller) :
    "Create a sequence of characters from a source of random rolls"
    for x in seqtools.chunker(newStats(roller), 6) :
        yield list(x)

def plotHistogram(roller) :
    cases = list(itertools.islice(newStats(roller),1000))

    def toBuckets(x) :
        "groups into 3 buckets (x <= 8) (8 < x < 13) (x >= 13)"
        if x <= 8 :
            return 1
        if x >= 13 :
            return 3
        return 2

    histogram.plot(cases)
    histogram.plot([toBuckets(x) for x in cases])
        
def test(seq) :
    "Do testy things with an input sequence of numbers"
    print (list(itertools.islice(seq, 12)))
    print (list(itertools.islice(newStats(seq), 12)))
    print (list(itertools.islice(newChars(seq), 4)))
    plotHistogram(seq)
    print ("---------------------")

    
if __name__ == '__main__' :

    shortdice = seqtools.bestof(range(3),3,4)
    nodice = itertools.cycle([1,2,3,4,5,6])
    dice = randoms(6)
    betterdice = seqtools.bestof(dice,3,4)
    evenbetterdice = seqtools.bestof(dice,3,5)
    stupiddice = seqtools.bestof(evenbetterdice,3,5)

    test(shortdice)
    test(nodice)
    test(dice)
    test(betterdice)
    test(evenbetterdice)
    test(stupiddice)

