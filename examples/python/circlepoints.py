#!/usr/bin/env python3

"""
Generate and print points on the radius of a circle. 
"""

import random
import math


def main(radius, count) :
    points = make_points(radius, count)
    print (count_quadrant(points))
    for x in points :
        print (x[0], x[1])

def count_quadrant(points) :
    quad = [0,0,0,0]
    for x in points :
        if x[0] >= 0 :
            if x[1] >= 0 :
                quad[0] += 1
            else:
                quad[3] += 1
        else :
            if x[1] >= 0 :
                quad[1] += 1
            else :
                quad[2] += 1

    return quad

def make_points(radius, count) :
    points = []
    for x in range(count) :
        p = make_point(radius)
        points.append(p)
    return points
    
def make_point(radius) :
    point1d = 2.0 * random.random() * math.pi
    return (radius * math.cos(point1d), radius * math.sin(point1d))

main(1000, 1000)
