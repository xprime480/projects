#!/usr/bin/env python3

import math

def logit2p(l) :
    """Convert a logit to a probability."""
    x = math.exp(l)
    return x/(1+x)

def p2logit(p) :
    """Convert a probability to a logit."""
    return math.log(p/(1-p))

def p2db(p) :
    """Convert a probability to a decibel."""
    return 10.0*math.log(p/(1-p), 10)

def db2p(db) :
    """Convert a decibel to a probability."""
    x = 10**(db/10.0)
    return x/(1+x)

if __name__ == '__main__' :
    print ('Run logittest.py for unit tests.')
