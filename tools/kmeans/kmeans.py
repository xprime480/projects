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

    def get_clusters(self) :
        return self.clusters

    def solve(self, data=[]) :
        self.data.extend(data)

        print (
            'Solving for %d clusters with %d data points' % (
                self.count, len(self.data)))

        if len(self.data) < self.count :
            raise Exception('Fewer data points than expected clusters')

        self.make_initial_clusters()
        for attempt in range(10) :
            self.assign_to_clusters()
            if self.test_clusters() :
                break
        print ('Solved in %d attempts' % attempt, file=sys.stderr)

        new_centroids = [self.centroid(c.get_items()) for c in self.clusters]
        self.clusters = [Cluster(c) for c in new_centroids]
        self.assign_to_clusters()

    def distance(self, p1, p2) :
        dx = 1.0 * (p2[0] - p1[0])
        dy = 1.0 * (p2[1] - p1[1])
        d  = math.sqrt(dx*dx + dy*dy)
        return d

    def centroid(self, items) :
        count = len(items)
        return (sum([i[0] for i in items])/1.0/count, 
                sum([i[1] for i in items])/1.0/count)

    def make_initial_clusters(self) :
        self.clusters = [Cluster(s)
                         for s in random.sample(self.data, self.count)]
        self.clusters = [Cluster(s) for s in self.data[:self.count]]

    def assign_to_clusters(self) :
        centroids = [c.get_centroid() for c in self.clusters]
        for d in self.data :
            imin = self.compute_cluster_ix(d, centroids)
            self.clusters[imin].add_item(d)

    def test_clusters(self) :
        new_centroids = [self.centroid(c.get_items()) for c in self.clusters]
        for ix in range(self.count) :
            for item in self.clusters[ix].get_items() :
                new_ix = self.compute_cluster_ix(item, new_centroids)
                if ix != new_ix :
                    self.clusters = [Cluster(c) for c in new_centroids]
                    return False
        return True

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
    data = [(0.26, 9.97), (1.48, 8.71), (0.15, 2.52), (4.31, 0.69), (5.48, 2.47), (4.72, 0.02), (6.44, 4.20), (8.23, 9.35), (9.24, 2.69), (9.36, 4.81)]

    solver.solve(data)
    clusters = solver.get_clusters()
    for c in clusters :
        print (c)

    dist = 0
    for c in clusters :
        ct = c.get_centroid()
        for i in c.get_items() :
            d = solver.distance(i, ct)
            dist += d
    print ('Total Distance = %f' % dist)

if __name__ == '__main__' :
    main()


