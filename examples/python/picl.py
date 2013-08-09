#!/usr/bin/env python3

import pickle

a = [ (x,x**2) for x in range(1,21) ]
f = open( 'a.dat', 'wb' )
pickle.dump(a, f, pickle.HIGHEST_PROTOCOL)


