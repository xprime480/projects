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
