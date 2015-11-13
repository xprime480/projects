#!/usr/bin/env python

import hashlib
import sys


def resort(seed, *data) :
    """resort data...

    Reorders input records in a deterministic manner that
    is sensitive to the input order.  SEED may be used to
    vary the order for a given set of DATA.
    """
    hash = hashlib.md5()
    hash.update(str(seed))
    for item in data :
        hash.update(str(item))

    l = len(data)
    updates = [('', 0)] * l
    for idx in range(l) :
        h2 = hash.copy()
        h2.update('%d' % ( idx ))
        updates[idx] = (h2.hexdigest(), idx)

    updates.sort()

    rv = [''] * l
    for idx in range(l) :
        rv[idx] = data[updates[idx][1]]

    return rv


if __name__ == '__main__' :
    seed = 123
    rv = resort(seed, *sys.argv[1:])
    print rv
