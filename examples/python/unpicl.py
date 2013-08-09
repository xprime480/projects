#!/usr/bin/env python3

import pickle

f = open( 'a.dat', 'rb' )
a = pickle.load(f)
print (a)



