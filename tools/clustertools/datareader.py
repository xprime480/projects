#!/usr/bin/env python3

def get_method(cls) :
    parts = cls.split('.')
    module = ".".join(parts[:-1])
    m = __import__( module )
    for comp in parts[1:]:
        m = getattr(m, comp)            
    return m

def get_data(key, cls, *args) :
    meth = get_method(key)
    data = meth(*args)
    return [cls.convert(d) for d in data]

