#!/usr/bin/env python

from htmlentitydefs import entitydefs
from BeautifulSoup import BeautifulSoup

def convertEntity(e, verbose=False):
    """Convert an html entity to the corresponding character

    Some corner cases not handled, such as '&junk&amp;' will try to handle
    the entire '&junk&amp;' as one entity and never discover the '&amp;'
    substring that is a valid entity.
    """
    converted = ''
    while len(e) :
        if verbose : print '*' * 64
        l, h = e.find('&'), e.find(';')
        if verbose : print e,l,h
        if h > l >= 0 :
            pre, t, e = e[:l], e[l:h+1], e[h+1:]
            if verbose : print '<%s><%s><%s>' % (pre, t, e)
            converted += pre
            x = t[1:-1]
            if x in entitydefs :
                converted += entitydefs[x]
            else :
                converted += '&'
                e = x + ';' + e
        elif l > h >= 0 :
            converted += e[:h+1]
            e         =  e[h+1:]
        else :
            converted += e
            e = ''
        if verbose: print '<<%s>><<%s>>' % (converted, e)
    return converted

def cookSoup(stream) :
    """Turn a stream into tag soup
    """
    soup = BeautifulSoup(stream.read())
    return soup
