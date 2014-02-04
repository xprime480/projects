#!/usr/bin/env python3

import itertools

class CategoryPoint2D(object) :
    def __init__(self) :
        pass

    @classmethod
    def distance(cls, p1, p2) :
        d = 0
        for ix in [0, 1] :
            if p1[ix] != p2[ix] :
                d += 1
        return d

    @classmethod
    def centroid(cls, items) :
        c = [None, None]
        for ix in [0, 1] :
            vs = [i[ix] for i in items]
            vs.sort()
            bestv = None
            bestl = 0
            for x in itertools.groupby(vs) :
                v = x[0]
                l = len(list(x[1]))
                if l > bestl :
                    bestl = l
                    bestv = v
            c[ix] = bestv

        return c
                
    @classmethod
    def convert(cls, item) :
        """This would be the place for conversions and validations.
        For now, just accept."""

        return item
