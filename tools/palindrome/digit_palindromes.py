#!/usr/bin/env python3

import math

################################################################
#
#
def to_digits(N, base) :
    """Return an array of the digits of N to the given BASE.

    Most significant digit is last in return value."""

    if N == 0 :
        return [0]

    digits = []
    while N > 0 :
        d = N % base
        digits.append(d)
        N = N // base

    return digits

################################################################
#
#
def from_digits(digits, base) :
    """Convert an array of digits in given BASE to a value.

    Assumes Most Significant Digit is last."""

    if max(digits) >= base :
        raise Exception('Invalid digit for base %d found in %s' % (base, str(digits)))

    return sum([digits[x] * (base ** x) for x in range(len(digits))])
    
################################################################
#
#
def count_palindromes(base, N) :
    """Compute approxminate number of palindromes in BASE up to N.

    The number computed is >= the correct number because number of is 
    computed up to the next power of base >= N.  For example if base 
    is 10 and N = 2032, the count of palindromes <= 9999 is computed.
    """
    
    ndigits = math.ceil(math.log(N)/math.log(base))

    if ndigits == 1 :
        return N

    count = base - 1
    for x in range(2, ndigits) :
        count += (base-1) * (base**(math.ceil(x/2.0)-1))

    digits = to_digits(N, base)
    half_digits = digits[-math.floor(len(digits)/2.0):]
    rhd = half_digits[:]
    rhd.reverse()

    t = from_digits(half_digits, base)

    if 1 == ndigits % 2 :
        count += (t-1) * (base-1)
        for x in range(base) :
            u = rhd[:]
            u.append(x)
            u.extend(half_digits)
            v = from_digits(u, base)
            if v <= N :
                count += 1
            else :
                break

    else :
        count += (t-1)
        u = rhd[:]
        u.extend(half_digits)
        v = from_digits(u, base)
        if v <= N :
            count += 1

    return count

################################################################
#
#
def tests() :
    print ([(x, count_palindromes(10, 10**x)) for x in range(1,11)])

    t = [(x, count_palindromes(x, 10**10)) for x in range(2,21)]
    print (t)
    t.sort(key=lambda x : x[1], reverse=True)
    print (t)

    print()
    print("note that digits are LSB first.""")

    for value, base in [(1234, 10), (1024,  2), (1024-1, 16)] :
        d = to_digits(value, base)
        v = from_digits(d, base)
        print (value, base, d, v)

    for digits, base in [([2, 3, 5], 10), ([2, 3, 11], 10)] :
        try : 
            v = from_digits(digits, base)
        except :
            v = 0
        d = to_digits(v, base)
        print (digits, base, v, d)

################################################################
#
#
def main() :
    #tests()

    for x in range(2, 30) :
        print ('%02d  %7d' % (x, count_palindromes(x, 10**10+1)))
    
################################################################
#
#
if __name__ == '__main__' :
    main()
