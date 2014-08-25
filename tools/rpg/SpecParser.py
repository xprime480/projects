#!/usr/bin/python3

import re

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
    def __init__(self) :
        self.pattern = re.compile('(\d*)d(\d+)(([+-])(\d+))?')

    def parse(self, spec) :
        matcher = self.match(spec)
        if not matcher :
            return None
        return self.generateResult(matcher)

    def match(self, spec) :
        return self.pattern.match(spec)
            
    def generateResult(self, matcher) :
        count  = self.parseCount(matcher)
        size   = self.parseSize(matcher)
        offset = self.parseOffset(matcher)
        return SpecParserResult(count, size, offset)

    def parseCount(self, matcher) :
        g1 = matcher.group(1)
        if g1 :
            return int(g1)
        return 1
        
    def parseSize(self, matcher) :
        return int(matcher.group(2))
        
    def parseOffset(self, matcher) :
        g3 = matcher.group(3)
        if g3 :
            return int(g3)
        return 0



