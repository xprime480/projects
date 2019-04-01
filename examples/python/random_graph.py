#!/bin/env python

import sys
import numpy as np
import time

def fill_graph(numNodes, numEdges) :
    edges = set()

    while len(edges) < numEdges :
        n1,n2 = np.random.choice(range(numNodes), 2, False)
        edges.add((min(n1,n2),max(n1,n2)));

    return sorted(list(edges))

def random_graph(numNodes, numEdges) :
    if numNodes < 2 :
        print('Graph too small for edges')
        sys.exit(1)

    edges = fill_graph(numNodes, numEdges)
    return edges

def full_graph(numNodes) :
    return [(a,b) for a in range(numNodes) for b in range(a+1,numNodes)]

def invert(numNodes, edges) :
    inverted = full_graph(numNodes)
    for e in edges :
        inverted.remove(e)
    return inverted

def degrees(numNodes, edges) :
    degrees = dict(zip(range(numNodes), [0] * numNodes))
    for n1,n2 in edges :
        degrees[n1] = degrees[n1] + 1
        degrees[n2] = degrees[n2] + 1

    counts = list(degrees.values())
    min_count = min(counts)
    max_count = max(counts)
    count_min = counts.count(min_count)
    count_max = counts.count(max_count)

    print('%d nodes have degree %s (minimum)' % (count_min, min_count))
    print('%d nodes have degree %s (maximum)' % (count_max, max_count))

def timer(f) :
        start = time.time()
        rv = f()
        end = time.time()
        print('%8.3f sec.' % (end - start))
        return rv

if __name__ == '__main__' :
    try :
        n,e = [int(arg) for arg in sys.argv[1:3]]

        edges = timer(lambda : random_graph(n, e))
        ##print edges
        degrees(n, edges)

        edges = timer(lambda : invert(n, edges))
        degrees(n, edges)

    except TypeError :
        print('Usage: random_grapy num_nodes num_edges')
        sys.exit(1)
    except ValueError :
        print('Parameters must be integers.')
        sys.exit(1)

