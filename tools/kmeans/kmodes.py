#!/usr/bin/env python3

#
# this file implements a generic k-modes classifier
#

import itertools

import ksolver

class KModesSolver(ksolver.KSolver) :
    def __init__(self, count, cls) :
        super().__init__(count, cls)

class CategoryPoint2D(object) :
    def __init__(self) :
        pass

    @classmethod
    def distance(self, p1, p2) :
        d = 0
        for ix in [0, 1] :
            if p1[ix] != p2[ix] :
                d += 1
        return d

    @classmethod
    def centroid(self, items) :
        c = [None, None]
        for ix in [0, 1] :
            vs = [i[ix] for i in items]
            vs.sort()
            bestv = None
            bestl = 0
            for x in itertools.groupby(vs) :
                v = x[0]
                l = len(list(x[1]))
                if l > bestl :
                    bestl = l
                    bestv = v
            c[ix] = bestv

        return c
                
data_set_1 = [
    (1,2), (1,3), (1,4), (2,5), (2,0), (3,5), (3, 7)
]

def main() :
    RANDOM_POINT_COUNT = 1000
    CLUSTER_COUNT = 3
    REPEAT_COUNT = 50

    #data = gen_data_1(RANDOM_POINT_COUNT, CLUSTER_COUNT)
    data = data_set_1[:]
    
    solver1 = KModesSolver(CLUSTER_COUNT, CategoryPoint2D)
    results1 = ksolver.run(solver1, data, REPEAT_COUNT)

    print (results1['distances'])
    print (results1)

if __name__ == '__main__' :
    main()
