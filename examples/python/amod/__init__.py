__version__ = '0.0.1'
__all__ = [ 'basic' ]

def basic(a, b) :
    from .first  import fnfirst
    from .second import fnsecond

    return fnfirst(a) + fnsecond(b)
