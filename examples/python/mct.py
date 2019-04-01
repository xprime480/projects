#!/usr/bin/env

def flurf(x) :
    return 'FLURF!'

class AMetaclass(type) :
    def __new__(cls, clsname, bases, dict) :
        altdict = { 'flurf' : flurf }
        altdict.update(dict)
        return type.__new__(cls, clsname, bases, altdict)


class A(object) :
    """Demonstrate basic metaclass behavior"""
    __metaclass__ = AMetaclass

class B(object) :
    """Demonstrate normal behavior"""
    pass

class C(A) :
    """Metaclass works through base classes as well"""
    pass

class D(A) :
    """This particular metaclass does not override flurf."""
    def flurf(self) :
        return 3

class E(D) :
    pass

class F(B, A) :
    pass

class G(C) :
    pass

for cls in [A, B, C, D, E, F, G] :
    try :
        v = cls().flurf()
        print cls, v
    except :
        print 'no flurf for', cls
