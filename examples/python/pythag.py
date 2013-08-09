from itertools import *
from math import sqrt
from mymath import *
from operator import itemgetter

def triples( max ) :
    for i in range( 1, max ) :
        for j in range ( i+1, max ) :
            k = hypot( i, j )
            if k < max and k == int( k ) and 1 == gcd( i, j ):
                yield ( i, j, int(k) )
    

tr = sorted( list( triples( 10000 ) ), key=itemgetter(2) )
#print (tr)

tr2 = [ p for h,p in
        [ ( k, list( g ) ) for k,g in groupby( tr, lambda t: t[2] ) ]
        if len( p ) > 1 ]
print (tr2)


