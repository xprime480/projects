#!/usr/bin/python3 

import itertools

def average_offset(n) :
    r = range(n)
    numerator = 0
    denominator = 0
    for x in itertools.permutations(r) :
        l = list(x)
        a = sum([abs(v-l[v]) for v in r]) / n
        numerator = numerator + a
        denominator = denominator + 1

    return round(numerator / denominator, 2)

for n in range(1,41) :
    print (n, average_offset(n))

