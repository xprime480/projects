#!/usr/bin/python3

import random

def foo(max_value) :
    r = range(max_value)
    values = random.sample(r,max_value)
    #print (values)
    return (sum([abs(values[i]-i) for i in r])/(max_value))

def main(max_value, repeat_count) :
    vals = [foo(max_value) for _ in range(repeat_count)]
    #print (vals)
    print (round(sum(vals) / repeat_count, 2))

if __name__ == '__main__' :
    import sys
    max_value = 100
    repeat_count = 1000
    

    if len(sys.argv) > 1 :
        try :
            max_value = int(sys.argv[1])
        except :
            pass

    if len(sys.argv) > 2 :
        try :
            repeat_count = int(sys.argv[2])
        except :
            pass

    main(max_value, repeat_count)
