#!/usr/bin/env python

class ABC(object) :
    def __init__(self) :
        pass

    def __repr__(self) :
        rep = ''
        for x in dir(self) :
            a = getattr(self, x)
            if len(x) >= 2 and 'r_' == x[:2] and callable(a) :
                t = a()
                if t :
                    rep += str(t)
        return rep


class Z(ABC) :
    def __init__(self) :
        ABC.__init__(self)

    def r_1(self) :
        return 'Hello, '

    def r_3(self) :
        return 'World'

class Zed(Z) :
    def __init__(self) :
        Z.__init__(self)

    def r_2(self) :
        return 'Lost '

class Q(ABC) :
    def __init__(self, v) :
        ABC.__init__(self)
        self.v = v

    def r_0(self) :
        return str(self.v)


print Z()
print Zed()
print Q(1)
print Q({})
