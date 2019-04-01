#!/usr/bin/env python

import random
import sys

class TestRandomWalk2D(object) :
    def __init__(self, height, width) :
        self.height = height
        self.width  = width

        self.moves = [ self.north, self.west, self.east, self.south ]

    def walk(self) :
        points = set([(h,w) for h in range(0,self.height) for w in range(0,self.width)])
        current = (random.randrange(0, self.height), random.randrange(0, self.width))
        points.remove(current)
        steps = 1

        while points :
            nh, nw = self.moves[random.randrange(4)](*current)
            if 0 <= nh <= self.height and 0 <= nw < self.width :
                current = (nh, nw)
                steps += 1
                if current in points :
                    points.remove(current)


        return steps

    def north(self, h, w) :
        return h-1, w

    def west(self, h, w) :
        return h, w-1
    
    def east(self, h, w) :
        return h, w+1

    def south(self, h, w) :
        return h+1, w

class TestRandomWalk2DTorus(TestRandomWalk2D) :
    def __init__(self, height, width) :
        TestRandomWalk2D.__init__(self, height, width)

    def north(self, h, w) :
        return (h-1+self.height)%self.height, w

    def west(self, h, w) :
        return h, (w-1+self.width)%self.width
    
    def east(self, h, w) :
        return h, (w+1)%self.width

    def south(self, h, w) :
        return (h+1)%self.height, w


def test(h, w, repeat, clskey='2D') :
    if repeat == 0 :
        return (None,None)

    if clskey == '2DTorus' :
        cls = TestRandomWalk2DTorus
    else :
        cls = TestRandomWalk2D

    t1 = cls(h,w)
    s1 = sum(t1.walk() for _ in range(repeat))
    a1 = (s1 * 1.0) / repeat
    return a1, a1 / h / w

def args() :
    """Parse and return the command line parameters."""

    import argparse
    import sys

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--height",
        help="number of rows in the maze",
        action='store', 
        default=3,
        nargs=1,
        type=int
    )
    parser.add_argument(
        "--width",
        help="number of columns in the maze", 
        default=3,
        nargs=1,
        type=int,
        action='store'
    )
    parser.add_argument(
        "--repeat",
        help="number of passes in the simulation", 
        default=1000,
        nargs=1,
        type=int,
        action='store'
    )
    parser.add_argument(
        "--type",
        help="what kind of graph to create", 
        default='2D',
        choices=['2D', '2DTorus'],
        nargs=1,
        action='store'
    )

    try :
        return parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

if __name__ == '__main__' :
    params = args()
    print(params)

    # the documentation says it won't work this way, but it does
    #
    h = params.height
    if type(h) == type([]) :
        h = h[0]

    w = params.width
    if type(w) == type([]) :
        w = w[0]

    r = params.repeat
    if type(r) == type([]) :
        r = r[0]

    print(test(h, w, r, params.type))
