#/usr/bin/env python3

import struct

print (struct.pack( '@2H', 23, 17 ))
print (struct.pack( '!2H', 23, 17 ))
print (struct.unpack( '<l', struct.pack( '4b', 0, 0, 0, 1 ) )[0])
print (struct.unpack( '@l', struct.pack( '8b', 0, 0, 0, 1, 0, 0, 0, 1 ) )[0])
