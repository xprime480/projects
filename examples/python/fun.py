#!/usr/bin/env python

import itertools as it
import numpy as np
import math

def best_n(seq, n, cmp=None) :
    if n <= 0 :
        return []

    tmp = sorted(seq, cmp=cmp)
    if len(tmp) <= n :
        return tmp

    return tmp[-n:]

def test_1() :
    s = range(5)
    print best_n(s, -5)
    print best_n(s, 0)
    print best_n(s, 3)
    print best_n(s, 5)
    print best_n(s, 8)
    print best_n(s, 3, cmp=lambda a,b: a-b)
    print best_n(s, 3, cmp=lambda a,b: b-a)

def d6s() :
    while True:
        yield np.random.random_integers(6)

def stats(ndice=3) :
    while True:
        yield sum(best_n(it.islice(d6s(), 0, ndice, 1), 3))

def chars(ndice=3, ntries=6) :
    while True:
        yield best_n(it.islice(stats(ndice), 0, ntries, 1), 6)

def sample_chars() :
    for d,t in [(3,6), (3,7), (4,6), (4,7)] :
        for c in it.islice(chars(ndice=d, ntries=t), 0, 6, 1) :
            print c
        print '-' * 40


def show_itertools() :
    print list(it.islice(it.count(5), 1, 40, 7))
    print list(it.islice(it.cycle(range(3)), 1, 10, 1))
    print list(it.repeat('test', 11))

    i1 = range(3)
    i2 = range(8)
    print list(it.chain(i1, i2))

    data = range(1,500,13)
    sel  = [False] * len(data)
    for x in range(len(data)) :
        y = x * (1+x) / 2
        if y >= len(data) :
            break
        sel[y] = True
        
    somenums = list(it.compress(data, sel))
    print somenums

    def fn(x) :
        return x < 100
    print list(it.dropwhile(fn, somenums))

    def kf(x) :
        return int(math.log(x, 10))
    for k,i in it.groupby(somenums, kf) :
        print '\t', k, list(i)

    def fn32(x) :
        return x % 3 == 2
    print list(it.ifilter(fn32, somenums))
    print list(it.ifilterfalse(fn32, somenums))

    def mod(x,y) :
        if y :
            return x % y
        return 0
    print list(it.imap(mod, somenums, it.count()))
    print list(it.starmap(mod, it.izip(somenums, it.count(2))))

    a,b,c = it.tee(somenums, 3)
    print list(it.izip(a, it.islice(b,1,None,1), it.islice(c,2,None,1)))

    print list(it.takewhile(fn, somenums))
    
    print list(it.izip(it.count(1), (i*i + i + 1 for i in range(1,13))))
    print list(it.izip_longest(range(1,4), (i*i + i + 1 for i in range(1,13))))

    print list(it.product((i*5 for i in [1.0,11.0,7.5]), range(4)))
    print list(it.permutations(range(4)))
    print list(it.permutations(range(4), 2))

    print list(it.combinations(range(4), 2))
    print list(it.combinations_with_replacement(range(4), 2))

def test_2() :
    data = np.random.standard_normal(30)
    ds = it.tee(data, 5)
    qs = it.izip(ds, it.count())
    for x in it.izip(*[it.islice(i,c,None,1) for i,c in qs]) :
        print sum(x)

def partial_sums(seq, reducer=None) :
    if not reducer :
        reducer = lambda a,b : a+b
        
    total = None
    for x in seq :
        if total is None :
            total = x
        else :
            total = reducer(total, x)
        yield total

def test_partial() :
    print list(partial_sums(xrange(1,5)))
    print list(partial_sums(xrange(1,5), lambda a,b : a*b))
    print list(partial_sums(it.islice(range(20),2,None,3)))

if __name__ == '__main__' :
    #test_1()
    #sample_chars()
    #show_itertools()
    #test_2()
    #test_partial()
    
    print np.floor([3.2], 1.0)


print help(np)
