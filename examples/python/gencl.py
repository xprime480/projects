#!/usr/bin/env python3

#
# admittedly very stupid
#

class Next10(object) :
    def __init__(self, k) :
        self.first = k
        self.last  = k + 10

    def __iter__(self) :
        return self

    def __next__(self) :
        if self.first < self.last :
            self.first += 1
            k = self.first
            return k
        raise StopIteration

def nother_test() :
    print(sum(i*i for i in range(5,8)))

if '__main__' == __name__ :
    print([x for x in Next10(3)])
    print(sum(Next10(5)))
    nother_test()
    n = Next10(892)
    print(next(n))
    print(tuple(n))
