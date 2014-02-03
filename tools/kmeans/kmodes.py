#!/usr/bin/env python3

#
# this file implements a generic k-modes classifier
#

import categorypoint2d
import ksolver

class KModesSolver(ksolver.KSolver) :
    def __init__(self, count, cls) :
        super().__init__(count, cls)

data_set_1 = [
    (1,2), (1,3), (1,4), (2,5), (2,0), (3,5), (3, 7)
]

def main() :
    RANDOM_POINT_COUNT = 1000
    CLUSTER_COUNT = 3
    REPEAT_COUNT = 50

    #data = gen_data_1(RANDOM_POINT_COUNT, CLUSTER_COUNT)
    data = data_set_1[:]
    
    solver1 = KModesSolver(CLUSTER_COUNT, categorypoint2d.CategoryPoint2D)
    results1 = ksolver.run(solver1, data, REPEAT_COUNT)

    print (results1['distances'])
    print (results1)

if __name__ == '__main__' :
    main()
