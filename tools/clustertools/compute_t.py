#!/usr/bin/env python3

import math

def get_data(file) :
    x = open(file)
    a = eval(x.readline())
    b = eval(x.readline())
    return [a,b]

def compute_mean(data) :
    return sum(data) / len(data)

def compute_sse(data) :
    mu  = compute_mean(data)
    sse = sum([x*x for x in [z - mu for z in data]])
    return sse

def compute_t(file) :
    data  = get_data(file)
    means = [compute_mean(x) for x in data]
    df    = sum([len(x) for x in data]) - 2
    sse   = [compute_sse(x)  for x in data]
    sp2   = (sse[0] + sse[1]) / df
    smm   = math.sqrt(sum([sp2/len(x) for x in data]))
    t     = (means[0]-means[1]) / smm
    return (t, df)

def main(file) :
    print (compute_t(file))

if __name__ == '__main__' :
    import sys
    main(sys.argv[1])


