#!/usr/bin/env python3

def count_parts(parts, low, high, total) :
    if (low * parts + (parts-1) * (parts) / 2) >= total :
        return 0

    if (high - low + 1) < parts :
        return 0
    
    if parts <= 0 :
        return 0

    if parts == 1 and low <= total <= high :
        return 1

    acc = 0
    for n in range(low, high) :
        acc += count_parts(parts-1, n+1, high, total-n)
    return acc


if __name__ == '__main__' :
    print (count_parts(5, 1, 55, 153))
