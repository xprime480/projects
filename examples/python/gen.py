#!/usr/bin/env python3

def sieve(k) :
    pin = list(range(2,k))
    pout = []
    while pin :
        pout.append(pin[0])
        for p in pout :
            pin = [x for x in pin if (x%p) != 0]
    return pout

def agen(i,k=3) :
    primes = sieve(k)
    if k not in sieve(k+1) :
        return
    while True :
        yield int(i)
        if i <= 1 :
            break
        for p in primes :
            if 0 == i % p :
                i = i / p
                break
        else :
            i = k * i + 1

records = { 'max' : (0,0), 'len' : (0,0) }
for n in range(2,2007) :
    ll = list(agen(n,41))
    m  = max(ll)
    l  = len(ll)
    if m > records['max'][0] :
        records['max'] = (m, ll)
    if l > records['len'][0] :
        records['len'] = (l, ll)
        
    
print(records)
        
