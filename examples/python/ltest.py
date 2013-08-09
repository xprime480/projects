#!/usr/bin/env python3


from counting import choose

def test() :
    a = float(39 * choose(59, 5))
    b = float(choose(59, 5))
    t = 0
    w = 0
    for n in range(4,59) :
        p = choose(n-1, 3)
        s = max(0, 59 - n)
        print (n, p, s)
        t += p * s
        w += s / b

    w /= 39
    print ()
    print (t * 39)
    print (a)
#    print (a)
    print (1.0 / w)

if __name__ == '__main__' :
    test()
