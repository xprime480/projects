#!/usr/bin/env python3

import datetime
import sys
import time

import datatable
import datatablefactory
import selectors

def withtimer(f) :
    def ff(*args) :
        t0 = datetime.datetime.now()
        rv = f(*args)
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
def add_one_million_rows(factory) :
    dt = factory.new_table('random', [('Random', int)])
    for x in range(1000000) :
        dt.add_row([x])
    return dt

@withtimer
def add_one_million_rows_range(factory) :
    dt = factory.new_table('random', [('Random', int)])
    dt.add_rows([(x,) for x in range(1000000)])
    return dt

def is_random_odd(x) :
    return x['Random'] % 2 == 1
    
__odd_selector = selectors.NamedSelector('Value', bool, is_random_odd)

@withtimer
def filter_one_million_rows(factory) :
    dt = add_one_million_rows(factory)
    df = dt.filter('Odds', __odd_selector)
    return df

@withtimer
def alt_filter_one_million_rows() :
    dt = add_one_million_rows()
    df = dt.alt_filter('Odds', __odd_selector)
    return df

def main() :
    factory = datatablefactory.DataTableFactory()
    factory.open()
    add_one_million_rows(factory)
    filter_one_million_rows(factory)
    add_one_million_rows_range(factory)
    factory.close()

if __name__ == '__main__' :
    main()
