#!/usr/bin/python3

#
# Test the speed of some ways of permuting ranges.
#

import random
import datetime

repeat_count = 10000
max_value    = 10000

def shuffle() :
    values = random.shuffle(list(range(max_value)))
    return values

def sample() :
    values = random.sample(range(max_value),max_value)
    return values

def index() :
    initial = [random.random() for x in range(max_value)]
    copy    = initial[:]
    copy.sort()
    values  = [initial.index(copy[i]) for i in range(max_value)]
    return values

def timeit(f) :
    start_time = datetime.datetime.now()
    for x in range(repeat_count) :
        f()
    end_time = datetime.datetime.now()

    elapsed = end_time - start_time
    print ('run time for function %s is %s.' % (f.__name__, elapsed))
    
                 

def main() :
    args = (repeat_count, max_value)
    print ('Testing %d repetitions of shuffling arrays of length %d' % args)

    for f in [shuffle, sample, index] :
        timeit(f)

if __name__ == '__main__' :
    main()
