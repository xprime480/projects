#!/usr/bin/env python3

import math

def logit2p(l) :
    """Convert a logit to a probability."""
    x = math.exp(l)
    return x/(1+x)

def p2logit(p) :
    """Convert a probability to a logit."""
    return math.log(p/(1-p))

def main() :
    """Execute some tests."""

    for x in range(-10,11) :
        print (logit2p(.25 * x))

    print (logit2p(p2logit(0.1)))


if __name__ == '__main__' :
    main()
