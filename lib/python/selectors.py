#!/usr/bin/env python3

import sys

class NamedSelector(object) :
    def __init__(self, name, the_type, func) :
        self.name = name
        self.func = func
        self.type = the_type

    def get_name(self) :
        return self.name

    def get_type(self) :
        return self.type
        
    def __call__(self, row) :
        return self.func(row)

def simple_column_selector(name, the_type, rename=None) :
    if rename is None :
        rename = name
        
    def f(row) :
        rv = row[name]
        try :
            return the_type(rv)
        except TypeError :
            return rv

    return NamedSelector(rename, the_type, f)

def get_non_nulls(ds, selector) :
    return [v for v in [selector(d) for d in ds] if v]

def _count_func(ds) :
    return len([d for d in ds])

def count_aggregator(name='Count') :
    return NamedSelector(name, int, _count_func)

def sum_aggregator(name, selector) :
    def _sum_func(ds) :
        return sum(get_non_nulls(ds, selector))

    return NamedSelector(name, selector.get_type(), _sum_func)

def average_aggregator(name, selector) :
    def _avg_func(ds) :
        vals = get_non_nulls(ds, selector)
        if len(vals) > 0 :
            return sum(vals) / len(vals)
        else :
            return 0

    return NamedSelector(name, float, _avg_func)

