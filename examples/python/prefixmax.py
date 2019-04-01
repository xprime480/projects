#!/usr/bin/python

from itertools import permutations
                      
def prefixmax(seq) :
    """"Get a strictly increasing subsequence of SEQ containing the first element..
    
    Assumes SEQ contains strictly positive integers.
    """

    pfm = []
    mx = 0
    for x in seq :
        if x > mx :
            mx = x
            pfm.append(x)
    return pfm

def average(nums) :
    if not nums :
        return 0

    return sum(nums) / len(nums)

def get_mx(sz) :
    """Compute the average length of strictly increasing subsequences of size SZ.

    The average is computed across all permutations of a sequence of SZ integers.
    Each subsequence includes the first element so might not be the maximal
    length subsequence of the permutation.
    """

    v = list(range(1, sz+1))
    gen = permutations(v)
    return average([1.0 * len(prefixmax(list(g))) for g in gen])

def main(lo, hi) :
    for v in range(lo, hi+1) :
        print '%3d %12.4f' % (v, get_mx(v))

if __name__ == '__main__' :
    main(1,20)

