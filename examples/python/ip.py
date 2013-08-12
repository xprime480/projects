#!/usr/bin/env python3

from itertools import starmap
from operator  import mul

x = range(0,5)
y = range(7,12)
print(sum(starmap(mul, zip(x,y))))
