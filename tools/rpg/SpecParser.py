#!/usr/bin/python3

import re

import combinator

class SpecParserResult(object) :
    def __init__(self, count, size, add) :
        self.count  = count
        self.size   = size
        self.add    = add

    def dice_count(self) :
        return self.count

    def dice_size(self) :
        return self.size

    def offset(self) :
        return self.add


class SpecParser(object) :
    def __init__(self, spec) :
        self.spec = spec
        self.data = spec
        self.count = 0
        self.size  = 0
        self.offset   = 0

    def parse(self) :
        self.data = self.spec

        if not self.parseCount() :
            return None

        if not self.skipD() :
            return None

        if not self.parseSize() :
            return None

        if not self.parseOffset() :
            return None

        return SpecParserResult(self.count, self.size, self.offset)
            
    def parseCount(self) :
        optCount = combinator.ZeroOneMatcher(combinator.IntegerMatcher())
        m,o,r = optCount.match(self.data)
        if m :
            self.count = o
        else :
            self.count = 1

        self.data = r
        return True

    def skipD(self) :
        d        = combinator.SingleCharMatcher('d')
        m,o,r = d.match(self.data)
        if not m :
            print ("bad spec: %s" % spec)
            return False

        self.data = r
        return True

    def parseSize(self) :
        size = combinator.IntegerMatcher()
        m,o,r = size.match(self.data)
        if not m :
            return False
        else :
            self.size = o

        self.data = r
        return True

    def parseOffset(self) :
        optAdder = combinator.ZeroOneMatcher(combinator.IntegerMatcher())
        m,o,r = optAdder.match(self.data)
        if m :
            self.offset = o
        else :
            self.offset = 0

        self.data = r
        return True


