#!/usr/bin/env python3

import io

s = io.StringIO('cat')
t = s.read( 4 )
s.write('fish')
s.seek(0)
s.write('es')
print ('[%s][%s]' %( t, s.getvalue()))
s.close()

q = open('sio.py')
print (q.read(10))

