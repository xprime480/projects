#!/usr/bin/python3

import operator

def merge(pdf1, pdf2, keyfunc=operator.add) :
    pdf = {}
    for k1,v1 in pdf1.items() :
        for k2,v2 in pdf2.items() :
            k = keyfunc(k1,k2)
            v = v1*v2
            if k in pdf.keys() :
                pdf[k] += v
            else :
                pdf[k] = v
    return pdf
