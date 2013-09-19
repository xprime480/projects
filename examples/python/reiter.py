#!/usr/bin/env python3

import re
import sys

test_string = '1329 xd 432 aosdf 9901'
test_re     = '(\\d+)'

def foo(a) :
    print(a)

for line in sys.stdin.readlines() :
    foo([m.group(1) for m in re.finditer(test_re, line)])
