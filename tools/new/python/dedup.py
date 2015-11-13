#!/usr/bin/python

def run(fn) :
    d = {}
    count = 0
    with open(fn) as f :
        for l in f.readlines() :
            count += 1
            d[l[:-1]] = count

    sl = [(v,k) for k,v in d.items()]
    sl.sort()
    for k,v in sl :
        print v

if __name__ == '__main__' :
    import sys
    for f in sys.argv[1:] :
        run(f)
