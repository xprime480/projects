#!/usr/bin/env python3

#
# this file implements a generic k-modes classifier
#

from datareader import get_data

import categorypoint2d
import ksolver

class KModesSolver(ksolver.KSolver) :
    def __init__(self, count, cls) :
        super().__init__(count, cls)

def main() :
    RANDOM_POINT_COUNT = 1000
    CLUSTER_COUNT = 3
    REPEAT_COUNT = 50

    data = get_data(
        'datamakers.data_set_1', 
        categorypoint2d.CategoryPoint2D
    )
    
    solver1 = KModesSolver(CLUSTER_COUNT, categorypoint2d.CategoryPoint2D)
    results1 = ksolver.run(solver1, data, REPEAT_COUNT)

    print (results1['distances'])
    print (results1)

if __name__ == '__main__' :
    main()
