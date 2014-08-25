#!/usr/bin/python3

import random

import PdfUtils

def get_new_dict() :
    return {}

def get_extended_roll() :
    xr = 0
    while True :
        r = random.randint(1,6)
        xr += r
        if r != 6 :
            break
    return xr-1

def make_a_roll(dice) :
    total = 0
    for die in range(dice) :
        r = random.randint(1,6)
        if r == 1 :
            r -= get_extended_roll()
        elif r == 6 :
            r += get_extended_roll()
        total += r
    return total

def add_roll_to_dict(d, r) :
    if r in d.keys() :
        d[r] += 1
    else :
        d[r] = 1

def counts_to_pdf(counts) :
    count = sum(counts.values())
    return dict([(k, 1.0 * v / count) for k,v in counts.items()])

def main() :
    counts = get_new_dict()
    for trials in range(int(1e6)) :
        r = make_a_roll(1)
        add_roll_to_dict(counts, r)
    pdf = counts_to_pdf(counts)

    PdfUtils.display(pdf, 8)

if __name__ == '__main__' :
    main()
