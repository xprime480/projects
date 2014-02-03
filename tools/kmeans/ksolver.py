
import random
import sys

from cluster import Cluster

def weighted_random_index(weights) :
    sum_weights = sum(weights)
    selector    = random.uniform(0.0, sum_weights)
    for ix in range(len(weights)) :
        sum_weights = sum_weights - weights[0]
        if sum_weights <= 0 :
            return ix
        
    return len(weights) - 1

class KSolver(object) :
    def __init__(self, count, cls) :
        self.count = count
        self.data = []
        self.clusters = []
        self.centroids = []
        self.cls = cls

    def get_clusters(self) :
        return self.clusters

    def distance(self, a, b) :
        return self.cls.distance(a, b)

    def centroid(self, items) :
        return self.cls.centroid(items)

    def solve(self, data, init_method=0) :
        self.data = data

        #print (
        #            'Solving for %d clusters with %d data points' % (
        #                self.count, len(self.data)))

        if len(self.data) < self.count :
            raise Exception('Fewer data points than expected clusters')

        self.initial_clusters(init_method)

        prior_centroids = []
        while self.centroids != prior_centroids :
            prior_centroids = self.centroids[:]
            self.centroids = [self.centroid(c.get_items()) for c in self.clusters]
            self.clusters = [Cluster(c) for c in self.centroids]
            self.assign_to_clusters()

        if min([len(c.get_items()) for c in self.clusters]) == 0 :
            print ('Error clustering: empty cluster(s)')
            print ([len(c.get_items()) for c in self.clusters])

    def initial_clusters(self, init_method) :
        # should set self.centroids to a list of centroids
        # should set self.clusters to a list of Cluster objects made 
        #      from those centroids
        # should call self.assign_to_clusters

        if init_method == 1 :
            self.centroids = self.init_max_distance()
        else :
            self.centroids = self.init_randomized()

        self.clusters = [Cluster(c) for c in self.centroids]
        self.assign_to_clusters()

    def init_randomized(self) :
        return random.sample(self.data, self.count)

    def init_max_distance(self) :
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

        return self.centroids



    def assign_to_clusters(self) :
        # should assign each datum in self.data to a cluster in self.clusters
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


def run(solver, data, repeat, init_method) :
    """Run SOLVER with DATA for REPEAT iterations.  Return all scores 
    and the cluster with the best score."""

    results = {}

    best_dist = sys.float_info.max
    best_clusters = None
    last_improvement = -1
    distances = []
    best_distances = []

    for x in range(repeat) :
        solver.solve(data, init_method)
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
            last_improvement = x

        distances.append(dist)
        best_distances.append(best_dist)

    return {
        'distances' : distances ,
        'best_distances' : best_distances ,
        'best' : best_dist ,
        'clusters' : best_clusters ,
        'last_improvement' : last_improvement
    }

