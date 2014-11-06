#!/usr/bin/python3

#
# See http://en.wikipedia.org/wiki/Secretary_problem
#
# This code does not give the predicted results.  The probability
# that the code is correct and still gives the results it does is
# close enough to zero that it must be assumed that there is a bug.
# 
# Possible sources for the discrepancy:
#  (1) the randomization of the vector is not "random enough."
#  (2) I don't understand what the original algorithm is supposed
#      to be doing
#  (3) I'm using some input incorrectly in the once function.  
#      Particular emphasis should be paid to the fraction parameter.
#  (4) I don't have a long enough array to notice the effects of the
#      algorithm.
#  (5) The main loop is not testing for max_arg_fraction correctly.
#  (6) Something else entirely.
#

import random

repeat_count = 1000
max_value    = 10

def once(fraction) :
    values = random.sample(range(1,1+max_value),max_value)
    cutoff = max(1,int(round(fraction * max_value)))
    target = max(values[:cutoff])

    for v in values[cutoff:] :
        if v > target :
            return v

    return values[-1]
                 

def main() :
    max_arg_fraction = .00
    max_sum          = 0
    for x in range(1,100) :
        fraction = x/100.0
        test_sum = sum([once(fraction) for _ in range(repeat_count)])
        if test_sum > max_sum :
            max_arg_fraction = fraction
            max_sum          = test_sum

    return max_arg_fraction


if __name__ == '__main__' :
    print ([main() for _ in range(100)])
