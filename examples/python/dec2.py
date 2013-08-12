#!/usr/bin/env python

def somedec( i=None ) :
    def wrap(f) :
        def t ( *args, **kw ) :
            print '-->', i
            f( *args, **kw )
            print '<--'
        return t
    return wrap


@somedec( i=13 )
def foo( a ) :
    print a


foo( 30 )

