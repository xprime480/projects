#!/usr/bin/python

import string
import random

keys = set([])

while len(keys) < 1000 :
    keys.add(''.join([random.choice(string.ascii_lowercase) for x in range(3)]))

keys.add('aaa')
keys.add('aaa')
keys.add('aaa')

lkeys = list(keys);

lkeys.sort()
for k in lkeys :
    print 'insert into key_names ( key_name ) value ( \'%s\' );' % k


