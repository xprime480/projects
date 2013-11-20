#!/usr/bin/python

def texify(name) :
    """Quote TeX special characters."""

    t = '\\_'.join(name.split('_'))
    t = '\\#'.join(t.split('#'))
    return t

