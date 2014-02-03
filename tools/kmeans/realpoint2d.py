#!/usr/bin/env python3

import math

class RealPoint2D(object) :
    def __init__(self) :
        pass

    @classmethod
    def distance(cls, p1, p2) :
        dx = 1.0 * (p2[0] - p1[0])
        dy = 1.0 * (p2[1] - p1[1])
        d  = math.sqrt(dx*dx + dy*dy)
        return d

    @classmethod
    def centroid(cls, items) :
        count = len(items)
        return (sum([i[0] for i in items])/1.0/count, 
                sum([i[1] for i in items])/1.0/count)

