#!/usr/bin/env python3

def factorial(x) :
    """Compute the factorial function of x (x!).

    """
    if type(x) != type(1) :
        return -1
    if x < 0 :
        return -1
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

    return factorial(n) / factorial(k) / factorial(n-k)

if __name__ == '__main__' :
    print ('Testing')
    print ('3! = ', factorial(3))
    print ('7! = ', factorial(7))
    print ('60! = ' , factorial(60))

    print ('(3 2) = ', choose(3, 2))
    print ('(6 3) = ', choose(6, 3))
    print ('(8 3) = ', choose(8, 3))
