#!/usr/bin/env python

#
# admittedly very stupid
#

class Next10(object) :
    def __init__(self, k) :
        self.first = k
        self.last  = k + 10

    def __iter__(self) :
        return self

    def next(self) :
        if self.first < self.last :
            self.first += 1
            k = self.first
            return k
        raise StopIteration

def nother_test() :
    print sum(i*i for i in xrange(5,8))

if '__main__' == __name__ :
    print [x for x in Next10(3)]
    print sum(Next10(5))
    nother_test()
    n = Next10(892)
    print n.next()
    print tuple(n)
