#!/usr/bin/env python3

from math import floor, sqrt
from mymath import gcd
import itertools

def triples( max ) :
    for k in range( 1, 1+max ) :
        imax = int( floor( sqrt( k*k/2.0 ) ) )
        for i in range( 1, 1+imax ) :
            j = sqrt( k*k - i*i )
            if abs( floor( j ) - j ) < 0.000001 and 1 == gcd( i, int( j ) ) :
                yield ( i, int( j ), k )
            


if __name__ == '__main__' :
    print(list( triples( 85 ) ))
    r = 0
    m = (0,0,0)
    for x in triples( 10000 ) :
        i,j,k = x
        t = (1.0 * i) / j
        if t > r :
            r = t
            m = x
            print (m)
    print (m)
    
