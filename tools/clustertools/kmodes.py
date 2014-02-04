#!/usr/bin/env python3

#
# this file implements a generic k-modes classifier
#

import datareader

import ksolver

def main() :
    RANDOM_POINT_COUNT = 1000
    CLUSTER_COUNT = 3
    REPEAT_COUNT = 50

    cls = datareader.get_method('categorypoint2d.CategoryPoint2D')
    data = datareader.get_data('datamakers.data_set_1', cls)
    
    solver1 = ksolver.KSolver(CLUSTER_COUNT, cls)
    results1 = ksolver.run(solver1, data, REPEAT_COUNT, 0)

    print (results1['distances'])
    print (results1)

if __name__ == '__main__' :
    main()
