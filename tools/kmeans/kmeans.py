#!/usr/bin/env python3

#
# this file implements a generic k-means classifier
#

import random
import sys

from cluster import Cluster
from datareader import get_data

import ksolver
import realpoint2d

def weighted_random_index(weights) :
    sum_weights = sum(weights)
    selector    = random.uniform(0.0, sum_weights)
    for ix in range(len(weights)) :
        sum_weights = sum_weights - weights[0]
        if sum_weights <= 0 :
            return ix
        
    return len(weights) - 1

class KMeansSolver(ksolver.KSolver) :
    def __init__(self, count, cls) :
        super().__init__(count, cls)

class KMeansSolverPlus(KMeansSolver) :
    def __init__(self, count, cls) :
        super().__init__(count, cls)

    def initial_clusters(self) :
        tdata = self.data[:]
        self.centroids = random.sample(tdata, 1)
        tdata.remove(self.centroids[0])
        for x in range(1, self.count) :
            weights = [min([self.distance(d,c) for c in self.centroids]) 
                       for d in tdata]
            ix      = weighted_random_index(weights)
            c       = tdata[ix]
            tdata.remove(c)
            self.centroids.append(c)

        self.clusters = [Cluster(c) for c in self.centroids]
        self.assign_to_clusters()

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
    
    solver1 = KMeansSolver(CLUSTER_COUNT, realpoint2d.RealPoint2D)
    solver2 = KMeansSolverPlus(CLUSTER_COUNT, realpoint2d.RealPoint2D)

    results1 = ksolver.run(solver1, data, REPEAT_COUNT)
    results2 = ksolver.run(solver2, data, REPEAT_COUNT)

    print (results1['distances'])
    print (results2['distances'])

if __name__ == '__main__' :
    main()
