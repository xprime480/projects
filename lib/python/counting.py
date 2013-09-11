#!/usr/bin/env python3

def factorial(x) :
    """Compute the factorial function of x (x!).

    """
    if type(x) != type(1) :
        return None
    if x < 0 :
        return None
    if x < 2 :
        return 1

    f = 1
    for n in range(2,x+1) :
        f *= n
    return f


def choose(n, k) :
    """Compute C(n, k).

    This represents the number of K-sized sets of N objects.  Order
    does not matter.
    """

    if k < 0 or n < 0 :
        return None
    if n < k :
        return 0
    if k == n : 
        return 1

    return factorial(n) // factorial(k) // factorial(n-k)

if __name__ == '__main__' :
    print ('Run countingtest.py for unit tests.')
