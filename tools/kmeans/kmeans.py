#!/usr/bin/env python3

#
# this file implements a generic k-means classifier
#

import math
import random
import sys

class Cluster(object) :
    def __init__(self, centroid) :
        self.centroid = centroid
        self.items    = []

    def add_item(self, item) :
        self.items.append(item)

    def get_items(self) :
        return self.items[:]

    def get_centroid(self) :
        return self.centroid

    def __repr__(self) :
        return '%s with centroid %s' % (str(self.items), str(self.centroid))


class KMeansSolver(object) :

    def __init__(self, count) :
        self.count = count
        self.data = []
        self.clusters = []
        self.centroids = []

    def get_clusters(self) :
        return self.clusters

    def solve(self, data=[]) :
        self.data = data

        #print (
        #            'Solving for %d clusters with %d data points' % (
        #                self.count, len(self.data)))

        if len(self.data) < self.count :
            raise Exception('Fewer data points than expected clusters')

        self.initial_clusters()
        prior_centroids = []
        while self.centroids != prior_centroids :
            prior_centroids = self.centroids[:]
            self.centroids = [self.centroid(c.get_items()) for c in self.clusters]
            self.clusters = [Cluster(c) for c in self.centroids]
            self.assign_to_clusters()

        if min([len(c.get_items()) for c in self.clusters]) == 0 :
            print ('Error clustering: empty cluster(s)')
            print ([len(c.get_items()) for c in self.clusters])

    def distance(self, p1, p2) :
        dx = 1.0 * (p2[0] - p1[0])
        dy = 1.0 * (p2[1] - p1[1])
        d  = math.sqrt(dx*dx + dy*dy)
        return d

    def centroid(self, items) :
        count = len(items)
        return (sum([i[0] for i in items])/1.0/count, 
                sum([i[1] for i in items])/1.0/count)

    def initial_clusters(self) :
        self.centroids = random.sample(self.data, self.count)[:]
        self.clusters = [Cluster(c) for c in self.centroids]
        self.assign_to_clusters()

    def assign_to_clusters(self) :
        for d in self.data :
            imin = self.compute_cluster_ix(d, self.centroids)
            self.clusters[imin].add_item(d)

    def compute_cluster_ix(self, item, centroids) :
        dmin = sys.float_info.max
        imin = self.count
        for ix in range(self.count) :
            dtest = self.distance(item, centroids[ix])
            if dtest < dmin :
                dmin = dtest
                imin = ix
            if imin >= self.count :
                raise Exception('Internal Error: bad distance metric')
        return imin

def main() :
    solver = KMeansSolver(3)

    #data = [(1,2), (1,3), (1,4), (2,5), (2,0), (3,5), (3, 7)]
    #data = [(random.uniform(0,10), random.uniform(0,10)) for _ in range(10)]
    #data = [(0.26, 9.97), (1.48, 8.71), (0.15, 2.52), (4.31, 0.69), (5.48, 2.47), (4.72, 0.02), (6.44, 4.20), (8.23, 9.35), (9.24, 2.69), (9.36, 4.81)]
    data = [(19, 51), (63, 2), (9, 30), (49, 62), (79, 90), (73, 85), (31, 19), (46, 76), (73, 5), (63, 59), (45, 16), (61, 81), (75, 20), (51, 93), (23, 54), (64, 58), (20, 4), (24, 33), (26, 95), (40, 43), (43, 10), (48, 36), (49, 94), (84, 87), (48, 30), (26, 54), (48, 71), (73, 86), (44, 18), (17, 39), (26, 73), (97, 91), (48, 12), (52, 12), (6, 10), (95, 41), (67, 35), (9, 27), (4, 56), (25, 96), (15, 97), (39, 64), (54, 69), (64, 13), (61, 50), (90, 23), (75, 55), (19, 92), (38, 89), (86, 10), (82, 54), (80, 22), (70, 12), (4, 53), (63, 90), (57, 48), (70, 27), (41, 21), (97, 5), (52, 30), (52, 65), (76, 38), (30, 54), (19, 39), (28, 81), (25, 78), (55, 14), (74, 19), (47, 43), (2, 24), (59, 100), (20, 24), (83, 82), (100, 79), (28, 27), (49, 36), (88, 81), (10, 73), (43, 19), (38, 42), (44, 88), (39, 1), (35, 27), (25, 93), (46, 62), (91, 38), (58, 65), (43, 51), (48, 26), (12, 75), (9, 41), (40, 44), (81, 66), (25, 34), (49, 28), (84, 7), (61, 72), (27, 13), (64, 7), (39, 69)]

    best_dist = sys.float_info.max
    best_clusters = None

    for x in range(50) :
        solver.solve(data)
        clusters = solver.get_clusters()

        dist = 0
        for c in clusters :
            ct = c.get_centroid()
            for i in c.get_items() :
                d = solver.distance(i, ct)
                dist += d

        if dist < best_dist :
            best_dist = dist
            best_clusters = clusters[:]

        print (dist, best_dist)

    print ('Total Distance = %f' % best_dist)
    for c in best_clusters :
        print (c)


if __name__ == '__main__' :
    main()


