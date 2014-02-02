#!/usr/bin/env python3

#
# this file implements a generic k-means classifier
#

import math
import random
import sys

from cluster import Cluster
import ksolver

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

class RealPoint2D(object) :
    def __init__(self) :
        pass

    @classmethod
    def distance(self, p1, p2) :
        dx = 1.0 * (p2[0] - p1[0])
        dy = 1.0 * (p2[1] - p1[1])
        d  = math.sqrt(dx*dx + dy*dy)
        return d

    @classmethod
    def centroid(self, items) :
        count = len(items)
        return (sum([i[0] for i in items])/1.0/count, 
                sum([i[1] for i in items])/1.0/count)

data_set_1 = [
    (1,2), (1,3), (1,4), (2,5), (2,0), (3,5), (3, 7)
]
data_set_2 = [
    (0.26, 9.97), (1.48, 8.71), (0.15, 2.52), (4.31, 0.69), 
    (5.48, 2.47), (4.72, 0.02), (6.44, 4.20), (8.23, 9.35), 
    (9.24, 2.69), (9.36, 4.81)
]
data_set_3 = [
    (19, 51), (63, 2), (9, 30), (49, 62), (79, 90), (73, 85), 
    (31, 19), (46, 76), (73, 5), (63, 59), (45, 16), (61, 81), (75, 20),
    (51, 93), (23, 54), (64, 58), (20, 4), (24, 33), (26, 95), (40, 43),
    (43, 10), (48, 36), (49, 94), (84, 87), (48, 30), (26, 54), 
    (48, 71), (73, 86), (44, 18), (17, 39), (26, 73), (97, 91), 
    (48, 12), (52, 12), (6, 10), (95, 41), (67, 35), (9, 27), (4, 56),
    (25, 96), (15, 97), (39, 64), (54, 69), (64, 13), (61, 50), 
    (90, 23), (75, 55), (19, 92), (38, 89), (86, 10), (82, 54), 
    (80, 22), (70, 12), (4, 53), (63, 90), (57, 48), (70, 27), (41, 21),
    (97, 5), (52, 30), (52, 65), (76, 38), (30, 54), (19, 39), (28, 81),
    (25, 78), (55, 14), (74, 19), (47, 43), (2, 24), (59, 100), 
    (20, 24), (83, 82), (100, 79), (28, 27), (49, 36), (88, 81), 
    (10, 73), (43, 19), (38, 42), (44, 88), (39, 1), (35, 27), (25, 93),
    (46, 62), (91, 38), (58, 65), (43, 51), (48, 26), (12, 75), (9, 41),
    (40, 44), (81, 66), (25, 34), (49, 28), (84, 7), (61, 72), (27, 13),
    (64, 7), (39, 69)
]

def gen_data_0(count) :
    gen = lambda : (random.uniform(0,10), random.uniform(0,10))
    data = [gen() for _ in range(count)]
    return data

def gen_data_1(count, n_clusters) :
    data = []
    for ix in range(n_clusters) :
        p = 20 * ix
        gen = lambda : (random.uniform(p,p+10), random.uniform(p,p+10))
        temp = [gen() for _ in range(count)]
        data.extend(temp)
    return data

def main() :
    RANDOM_POINT_COUNT = 1000
    CLUSTER_COUNT = 3
    REPEAT_COUNT = 50

    #data = gen_data_0(RANDOM_POINT_COUNT)
    
    data = gen_data_1(RANDOM_POINT_COUNT, CLUSTER_COUNT)
    
    solver1 = KMeansSolver(CLUSTER_COUNT, RealPoint2D)
    solver2 = KMeansSolverPlus(CLUSTER_COUNT, RealPoint2D)

    results1 = ksolver.run(solver1, data, REPEAT_COUNT)
    results2 = ksolver.run(solver2, data, REPEAT_COUNT)

    print (results1['distances'])
    print (results2['distances'])

if __name__ == '__main__' :
    main()
