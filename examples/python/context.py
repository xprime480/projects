#!/usr/bin/env python3

import contextlib
import random

@contextlib.contextmanager
def tag(name):
    print("<%s>" % name)
    yield
    print("</%s>" % name)

with tag("h1"):
    print("foo")


@contextlib.contextmanager
def single_random_int(m) :
    t = random.randint(1, m)
    yield t

with single_random_int(100) as v :
    print (v)

with contextlib.closing(open('context.py')) as f :
    print (len(f.readlines()))
