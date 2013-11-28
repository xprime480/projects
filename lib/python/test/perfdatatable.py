#!/usr/bin/env python3

import datetime
import sys
import time

import datatable
import selectors

def withtimer(f) :
    def ff() :
        t0 = datetime.datetime.now()
        rv = f()
        t1 = datetime.datetime.now()
        elapsed = t1-t0
        print (
            '%s ran in %d days, %d.%06d seconds' % 
            (f.__name__, elapsed.days, elapsed.seconds, elapsed.microseconds),
            file=sys.stderr
        )
        return rv

    return ff

@withtimer
def add_one_million_rows() :
    dt = datatable.DataTable('random', ['Random'])
    for x in range(1000000) :
        dt.add_row([x])
    return dt
    
@withtimer
def filter_one_million_rows() :
    dt = add_one_million_rows()
    __odd_selector = selectors.NamedSelector(
        'Value', 
        lambda x : (x['Random'] % 2) == 1
    )
    df = dt.filter('Odds', __odd_selector)
    return df


@withtimer
def alt_filter_one_million_rows() :
    dt = add_one_million_rows()
    __odd_selector = selectors.NamedSelector(
        'Value', 
        lambda x : (x['Random'] % 2) == 1
    )
    df = dt.alt_filter('Odds', __odd_selector)
    return df

def main() :
    add_one_million_rows()
    filter_one_million_rows()

if __name__ == '__main__' :
    main()
