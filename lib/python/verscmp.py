#!/usr/bin/env python3


def components( v ) :
    """split a string into its numeric, dot-separated components"""

    return [ int( x ) for x in v.split( '.' ) ]


def verscmp( x, y ) :
    """Sort two version string that look like NN[.NN]*

    where NN >= 0 and at least one NN is not zero"""
    
    def strip_trailing_zeros( l ) :
        """strip all trailing zeroes from a list."""
        while len( l ) > 0 and l[ -1 ] == 0 :
            l = l[ : -1 ]
        return l

    def cmp(a, b) :
        """return -1,0,or +1 as a < == or > b.

        Python3 no longer supports cmp."""

        return ((a>b) - (a<b))

    xs = strip_trailing_zeros( components( x ) )
    ys = strip_trailing_zeros( components( y ) )
    ml = min( len( xs ), len( ys ) )
    cs = [ cmp(xs[ i ], ys[ i ]) for i in range( ml ) ]
    if 0 in cs :
        cs.remove( 0 )
    return len( cs ) > 0 and cs[0] or cmp( len( xs ), len( ys ) )

if '__main__' == __name__ :
    print ('Run verscmptest.py for unit tests.')
