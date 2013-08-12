#!/usr/bin/env python

import operator
from itertools import *

class Bango :
    """Iterator class over a range defined by an intial value, a max value,
    and a way to compute a next value from a given value.
    """
    
    def __init__(self, first, last, func) :
        """Initalize the endpoints and incrementor"""
        self.first = first * 1.0
        self.last  = last
        self.func  = func

    def __iter__(self) :
        """Return ourselves as a iterator"""
        return self

    def next(self) :
        """Return the next value in our generated sequence"""
        t = self.first
        if t >= self.last :
            raise StopIteration
        self.first = self.func(self.first)
        return t

def func1(val) :
    """Compute v + sqrt(v)"""
    from math import sqrt
    v = 1.0 * val
    return v + sqrt(v)

def gen_f(min, max, f) :
    """Geneate sequence a defined by a[n+1] = f(a[n])"""
    t = min
    while t < max :
        yield t
        t = f(t)

def gen_fib() :
    """Generate standard Fibonacci sequence"""
    a,b = 1,1
    while True :
        yield a
        a,b = b,a+b


def fibish(a,b,c) :
    """Generate sequence defined by a[n+3] = a[n] + a[n+1], given a[0:3]"""
    while True :
        yield a
        a,b,c = b,c,a+b

print list(izip(count(1), Bango(1, 100, func1)))
print list(gen_f(1, 100, func1))

print list(imap(operator.pow, xrange(1,5), repeat(3)))

def listn(s,n) :
    """generate the first n items of an input generator"""
    return list(islice(s,n))

print listn(gen_fib(), 12)              # 12 fibonacci numbers
print listn(fibish(0,1,1), 30)          # 30 numbers from a sequence

s1 = [1,2,3]
s2 = (7,6,5,4)
s3 = {1:7, 10:15}
print list(chain(s1,s2,s3))             # s1, s2, s3 concatenated

i1 = count(89)
print listn(i1, 5)                      # 5 ints starting at 89

i2 = cycle([3,2])
print listn(i2, 7)                      # 3,2,3,2,... to 7 items

i3 = dropwhile(lambda i: i < 100, i1)
print listn(i3, 5)                      # first 5 items from i1 >= 100

def tiny(i) :
    return i < 5

print [(k,list(g))                      # segment by large/small
       for k,g in groupby(chain(s1,s2), tiny)]
print [list(g)                          # show segments of large/small
       for k,g in groupby(chain(s1,s2), tiny)]
print list(ifilter(tiny, chain(s1,s2))) # show only small
print list(ifilterfalse(tiny,           # show only large
                        chain(s1,s2)))
print list(imap(operator.mul, s1, s2))  # multiply corresponding parts
print list(islice(i2, 3))               # first 3
print list(islice(i2, 2, 5))            # items 2..5
print list(islice(i3, 18, 27, 2))       # every other item from 18..27
print list(izip(i2, count(1),           # combine 3 ranges
                xrange(10)))
print list(repeat(['a', 'b'], 5))       # doh
print list(starmap(operator.pow,        # exponentiate given pairs
                   [(3.0, 2.2), (1.223, 7.5)]))
print list(takewhile(tiny,              # leading small subsequence
                     chain(s1,s2)))
print list(chain(*tee(s1, 3)))          # repeat the sequence

import random
def seqi(X, Y) :
    """ Generate a sequence s.such that a for any values, v1, v2, in xrange(X)
    and for any leading subsequence, t, of s:
    
            v1 < v2 --> t.count(v1) >= t.count(v2)

    and

            s has at least one value == X-1

    and for any v in xrange(X)

            s.count(v) < Y.
"""
    i5 = tee(xrange(X), Y)
    o5 = []
    while True :
        try :
            x = random.choice(i5).next()
        except StopIteration :
            break
        o5.append(x)
    return o5

print seqi(5,5)
print seqi(5,5)
print seqi(5,5)
print seqi(5,5)

# 128 random bits
#
print ''.join([str(x)
               for x in islice(starmap(random.randint, repeat((0, 1))), 128)])

#
# arbitrary polynomial
#
print list(imap(lambda x: x*x + 3*x + 4, islice(count(1), 5)))
