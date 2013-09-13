#!/usr/bin/env python3

"""Simulate some random choices of permutations."""

import math
import random

################################################################
#
def inner_product(a) :
    """Compute the inner product of a vector of numbers."""

    return math.sqrt(sum([(i - a[i]) ** 2 for i in range(len(a))])) / len(a)

################################################################
#
def args() :
    """Parse and return the command line parameters."""

    import argparse
    import sys

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--item_count",
        help="number of items in the simulation", 
        default=50,
        nargs='?',
        type=int
    )
    parser.add_argument(
        "--pass_count",
        help="number of passes in the simulation", 
        default=52,
        nargs='?',
        type=int
    )
    parser.add_argument(
        "--trials_per_pass",
        help="number of trials for each pass", 
        default=7,
        nargs='?',
        type=int
    )
    parser.add_argument(
        "--trial_size",
        help="number of items in each trial", 
        default=6,
        nargs='?',
        type=int
    )

    try :
        return parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

################################################################
#
def main(spec) :
    """Run the simulation."""

    if (spec.trial_size + spec.trials_per_pass) > spec.item_count :
        print ('There are not enough items ')
        return

    x = [i for i in range(spec.item_count)]
    h = [0 for i in range(spec.item_count)]

    for r in range(spec.pass_count) :
        y = []
        for q in range(spec.trials_per_pass) :
            ix = random.randint(0,spec.trial_size - 1)
            z = x[ix]
            h[z] += 1
            x.remove(z)
            y.append(z)

        random.shuffle(y)
        x.extend(y)

    print (h)


if __name__ == '__main__' :
    main(args())
