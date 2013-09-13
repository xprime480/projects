#!/usr/bin/env python3

import unittest

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

class ClassDecTests(unittest.TestCase) :
    def test_basic(self) :
        s = S(2)
        t = T(7)
        
        self.assertEqual('2', str(s));
        self.assertEqual('8', str(t));
        self.assertEqual( 5, s.op('+', 3))
        self.assertEqual(14, s.op('*', 7))
        self.assertEqual(8, t.op('*', s.op('-', 1)))

def main() :
    unittest.main()

if __name__ == '__main__' :
    main()
