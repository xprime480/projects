#!/usr/bin/python

import sys

def get_lines(f) :
    with open(f, "r") as h :
        raw = [x[:-1] for x in h.readlines() if x[:-1]]

    raw.sort()
    return raw

def remove_prefixes(data, str) :
            str = l[:-1]
            if str :
                sz = len(str)
                mx = len(data)
                data.extend([None] * (sz-mx+1))

                for i in range(1,sz+1) :
                    prefix = str[:i]
                    if prefix in 
        

def find_non_prefix(f) :
    input = get_lines(f)
    if not input :
        return

    output = [None] * (len(input[-1]) + 1)
    for str in input :
        remove_prefixes(output, str)
        output[len(str)].append(str)

if __name__ == '__main__' :
    find_non_prefix(sys.argv[1])
