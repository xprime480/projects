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

def mean(pdf) :
    return sum([k*v for k,v in pdf.items()])

def variance(pdf) :
    mu = mean(pdf)
    return sum([(k-mu)*(k-mu)*v for k,v in pdf.items()])

def get_sorted_dict_keys(d) :
    ks = list(d.keys())
    ks.sort()
    return ks

def display(d, roundto=3) :
    ks = get_sorted_dict_keys(d)
    for k in ks :
        if round(d[k], roundto) > 0 :
            print ('%5d %f' % (k, d[k]))
    print ()
    print ('mean = %f' % mean(d))
    print ('stddev = %f' % variance(d) ** 0.5)

