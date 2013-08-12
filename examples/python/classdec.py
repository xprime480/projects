#!/usr/bin/env python

def seq() :
    t = 1
    while True :
        yield t
        t += 1

g = seq()

def trace(f) :
    def tracer(*args) :
        s = next(g)
        print('in', s, f)
        v = f(*args)
        print('out', s)
        return v
    return tracer

class S(object) :
    def __init__(self, i) :
        self.i = i

    def __new__(cls, i) :
        print('creating a', cls)
        o = super(S, cls).__new__(cls)
        o.__init__(i)
        return o

    def __str__(self) :
        return str(self.i)

    def __repr__(self) :
        return repr(self)

    @trace
    def op(self, op, arg) :
        return eval('self.i %s %d' % (op, arg))

class T(S) :
    def __init__(self, i) :
        self.i = i+1

s = S(2)
t = T(7)
print(s,t)
print(s.op('+', 3))
print(s.op('*', 7))
print(t.op('*', s.op('-', 1)))
