#!/usr/bin/env python3

#
# this file implements a generic k-means classifier
#

import random
import sys

from datareader import get_data

import ksolver
import realpoint2d

def main() :
    RANDOM_POINT_COUNT = 1000
    CLUSTER_COUNT = 3
    REPEAT_COUNT = 50

    data = get_data(
        'datamakers.gen_data_1', 
        realpoint2d.RealPoint2D, 
        RANDOM_POINT_COUNT, 
        CLUSTER_COUNT
    )
    
    solver = ksolver.KSolver(CLUSTER_COUNT, realpoint2d.RealPoint2D)

    results1 = ksolver.run(solver, data, REPEAT_COUNT, 0)
    results2 = ksolver.run(solver, data, REPEAT_COUNT, 1)

    print (results1['distances'])
    print (results2['distances'])

if __name__ == '__main__' :
    main()
