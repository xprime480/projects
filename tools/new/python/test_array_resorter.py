#!/usr/bin/env python

import array_resorter
import itertools

input_data = [ 1,2,3,4,5,6 ]
counts = dict([(q,0) for q in itertools.permutations(input_data, len(input_data))])

for seed in range(6*5*4*3*2*1*20) :
    t = tuple(array_resorter.resort(seed, *input_data))
    counts[t] = counts[t] + 1

print dict([(n,len(list(i))) for n,i in itertools.groupby(sorted(counts.values()))])

