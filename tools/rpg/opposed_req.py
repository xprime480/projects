#!/usr/bin/python3

import operator

import DicePdf
import PdfUtils

def resolver(a, d) :
    x = a - d
    if x >= 0 :
        return x // 5
    else :
        return -1 * (abs(x) // 5)

def resolve(a, d) :
    t2 = PdfUtils.merge(a, d, resolver)
    PdfUtils.display (t2)
    print ("----------------------")

        
def main() :
    d8   = DicePdf.DicePdf("8d6").get()
    d7p3 = DicePdf.DicePdf("7d6+3").get()

    resolve(d8, d7p3)

    d20 = DicePdf.DicePdf("20d6").get()
    resolve(d20, d20)

    d2 = DicePdf.DicePdf("2d6").get()
    resolve(d2, d2)

    resolve(d20, d2)

if __name__ == '__main__' :
   main()
