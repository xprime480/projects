#!/usr/bin/env python3

from itertools import *
from operator import *
import random

r = range(100)
s = range(3)

print(list(r))
print(list(islice(r, 10)))
print(list(islice(r, 10, 20)))
print(list(islice(r, 10, 20, 3)))
print(list(chain(islice(r, 10, 20, 3), islice(r, 50, 70, 5))))
q = list(zip(islice(r, 10, 20, 3), islice(r, 50, 70, 5)))
print(q)
t = list(takewhile(lambda x : x < 12, r))
t.reverse()
print(t)
print(list(map(sum, q)))
print(list(starmap(mul, q)))
print(list(islice(dropwhile(lambda x : x < 1023, count(560)), 10)))
print(list(repeat('a', 3)))
print(list(islice(cycle(s), 8)))
print(list(map(add, count(1), r)))


p = list(r)
random.shuffle(p)
print(p)
print(list([x for x in list(random.__dict__.keys()) if x[0] != '_']))

print([len(list(g)) for
       k,g in groupby(p, lambda x : x%2)])

print(list(filterfalse(lambda x : 3 == (x % 7), p)))

iters = tee(p, 11)
l = len(iters)
v = []
for i in range(l) :
    v.append(list(filter(lambda x : i == (x % l), iters[i])))
print(v)

print((list(chain(*v))))
