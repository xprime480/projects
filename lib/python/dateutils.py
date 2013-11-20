#!/usr/bin/python3

import datetime
import itertools

def all_date_formats() :
    """Return a long list of possible date formats usable by e..g strptime."""

    now = datetime.datetime.now()

    year_fmts  = ['%y', '%Y']
    month_fmts = ['%m', '%b', '%B']
    day_fmts   = ['%d']
    seps       = ['', '/', '-', ' ']

    for x in itertools.product(year_fmts, month_fmts, day_fmts) :
        for y in itertools.permutations(x, 3) :
            for sep in seps :
                yield sep.join(y)

    yield '%B %d, %Y'           # January 17, 1960
    yield '%b %d, %Y'           # Jan 17, 1960

def all_dates(vs) :
    """Test if all the inputs are probably dates.

       VS is an iterable that returns strings.
    """

    fmts = list(all_date_formats())

    for v in vs :
        tfmts = fmts[:]
        fmts  = []
        for f in tfmts :
            try :
                d = datetime.datetime.strptime(v, f)
                if not 1900 <= d.year <= 2100 :
                    continue
                fmts.append(f)
            except ValueError :
                pass
        if not fmts :
            break

    return fmts
