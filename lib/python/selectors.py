#!/usr/bin/env python3

class NamedSelector(object) :
    def __init__(self, name, func) :
        self.name = name
        self.func = func

    def get_name(self) :
        return self.name

    def __call__(self, row) :
        return self.func(row)

def simple_column_selector(name, rename=None) :
    if rename is None :
        rename = name

    return NamedSelector(rename, lambda x : x[name])

def get_non_nulls(ds, selector) :
    return [v for v in [selector(d) for d in ds] if v]

def _count_func(ds) :
    return len([d for d in ds])

def count_aggregator(name='Count') :
    return NamedSelector(name, _count_func)

def sum_aggregator(name, selector) :
    def _sum_func(ds) :
        return sum(get_non_nulls(ds, selector))

    return NamedSelector(name, _sum_func)

def average_aggregator(name, selector) :
    def _avg_func(ds) :
        vals = get_non_nulls(ds, selector)
        if len(vals) > 0 :
            return sum(vals) / len(vals)
        else :
            return 0

    return NamedSelector(name, _avg_func)

