#!/usr/bin/env python3

"""Prime number sieve."""

def sieve(k) :
    """Prime number sieve for all primes up to and including K."""

    pin = list(range(2,k))
    pout = []
    while pin :
        pout.append(pin[0])
        pin = pin[1:]
        if not pin :
            break
        for p in [q for q in pout if q*q <= pin[-1]] :
            pin = [x for x in pin if (x%p) != 0]
    return pout

if __name__ == '__main__' :
    print ('Run sievetest.py for unit tests.')
