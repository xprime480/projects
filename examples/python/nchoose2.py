#!/usr/bin/env python3

def pairs( n ) :
    for x in range(1, n+1) :
        for y in range(x+1, n+1) :
            yield (x,y)

if __name__ == '__main__' :
    from sys import argv
    if len( argv ) < 2 :
        n = 3
    else :
        n = int( argv[ 1 ] )
    for i,j in pairs( n ) :
        print (i,j)
    

    import random
    def f() :
        return int(random.uniform(0,1) < (2.0/n))
        
    k = int(n*(n-1)/2)
    print (sum([ f() for x in range(k) ]))
    print (random.sample( range(1,n+1), 2 ))
