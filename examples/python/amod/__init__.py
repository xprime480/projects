__version__ = '0.0.1'
__all__ = [ 'basic', 'first', 'second' ]

from .first  import first
from .second import second

def basic(a, b) :
    return first(a) + second(b)


