#!/usr/bin/python3

import imp

def mod_test(mod) :
    print (mod.hat)
    
    if 'back_link' in dir(mod) :
        mod_test(mod.back_link)

try :
    q = imp.find_module('test_data')
    test_data = imp.load_module('test_data', q[0], q[1], q[2])
    q[0].close()
    del(q)
    print (test_data.secret)
except ImportError as e :
    print (e)

q = imp.new_module('randy')
q.hat = 'fedora'
mod_test(q)

r = imp.new_module('sandy')
r.hat = 'derby'
r.back_link = q
mod_test(r)

print (dir(r))

import test_data as td2
print (td2.secret)

import test_data as td3
print (td2.secret)
