#!/usr/bin/env python3

import cmath

i = cmath.sqrt(-1)
print (i)
print (cmath.sqrt(i))
print (cmath.sqrt(cmath.sqrt(i)))
print (cmath.exp(1j * cmath.pi))

def f() :
    return random.randint(1,100)

import random
print ([max(min(f(),f()),min(f(),f())) for x in range(10)])

