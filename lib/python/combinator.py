#!/usr/local/bin/python

############################################

class Combinator :
    def match(self, input) :
        return (None, None, input)

    def validate(self, input) :
        if type(input) != type('') :
            return False
        if len(input) == 0 :
            return False
        return True

############################################
    
class SingleCharMatcher(Combinator) :
    def __init__(self, char) :
        self.char = char

    def match(self, input) :
        if not self.validate(input) :
            return (None, None, input)
        if self.char == input[0] :
            return (self.char, self.char, input[1:])
        return (None, None, input)

############################################

class CharSetMatcher(Combinator) :
    def __init__(self, chars) :
        self.chars = chars

    def match(self, input) :
        if not self.validate(input) :
            return (None, None, input)
        ch = input[0]
        if ch in self.chars :
            return (ch, ch, input[1:])
        return (None, None, input)

############################################

class CharRangeMatcher(Combinator) :
    def __init__(self, min, max) :
        self.min = min
        self.max = max
    
    def match(self, input) :
        if not self.validate(input) :
            return (None, None, input)
        ch = input[0]
        if self.min <= ch <= self.max :
            return (ch, ch, input[1:])
        return (None, None, input)

############################################
    
class AnyCharMatcher(Combinator) :
    def match(self, input) :
        if not self.validate(input) :
            return (None, None, input)
        ch = input[0]
        return (ch, ch, input[1:])

############################################

class AnyOfMatcher(Combinator) :
    def __init__(self, *parsers) :
        self.parsers = parsers

    def match(self, input) :
        for p in self.parsers :
            matched,obj,rest = p.match(input)
            if matched is not None :
                return (matched,obj,rest)

        return (None, None, input)

############################################

class ZeroPlusMatcher(Combinator) :
    def __init__(self, parser) :
        self.parser = parser

    def match(self, input) :
        if type(input) != type('') :
            return (None, None, input)

        matched = ''
        objs = []
        rest = input
        while True :
            m,o,rest = self.parser.match(rest)
            if m == None :
                return (matched, objs, rest)

            objs.append(o)

            if m == '' :
                return (matched, objs, rest)
            
            matched = matched + m
    
############################################

class ZeroOneMatcher(Combinator) :
    def __init__(self, parser) :
        self.parser = parser

    def match(self, input) :
        m,o,rest = self.parser.match(input)
        if m != None :
            return (m,o,rest)
        return ('', None, input)

############################################

class OnePlusMatcher(ZeroPlusMatcher) :
    def __init__(self, parser) :
        ZeroPlusMatcher.__init__(self, parser)

    def match(self, input) :
        m,o,rest = ZeroPlusMatcher.match(self, input)
        if m != None and len(o) > 0:
            return (m,o,rest)
        return (None, None, input)

############################################

class IntegerMatcher(Combinator) :
    def match(self, input) :
        signMatcher = ZeroOneMatcher(CharSetMatcher('-+'))
        sign,_,rest = signMatcher.match(input)

        digits = OnePlusMatcher(CharSetMatcher("0123456789"))
        m,o,rest = digits.match(rest)
        if m == None :
            return (m,o,input)

        val = int(m)
        if sign == '-' :
            m = sign + m
            val *= -1
        elif sign == '+' :
            m = sign + m
            
        return (m, val, rest)

############################################

class SequenceMatcher(Combinator) :
    def __init__(self, *parsers) :
        self.parsers = parsers

    def match(self, input) :
        m = ""
        os = []
        rest = input
        for p in self.parsers :
            matched,o,rest = p.match(rest)
            if matched is None :
                return (None,None,input)
            m = m + matched
            os.append(o)

        return (m, os, rest)

############################################

class StringMatcher(Combinator) :
    def __init__(self, string) :
        self.string = string
        self.len = len(self.string)

    def match(self, input) :
        if not self.validate(input) :
            return (None, None, input)

        if input.find(self.string) == 0 :
            return (self.string, self.string, input[self.len:])

        return (None, None, input)
        
############################################

class ListMatcher(Combinator) :
    def __init__(self, items, seps) :
        self.items = items
        self.seps  = seps

    def match(self, input) :
        m = ''
        os = []

        matched,o,rest = self.items.match(input)
        if matched is None :
            return None,None,input

        m = m + matched
        os.append(o)

        opt_items = SequenceMatcher(self.seps,self.items)
        while True :
            save = rest[:]
            matched,o,rest = opt_items.match(save)
            if matched is None :
                return m,os,save

            m = m + matched
            os.append(o[1])
        
################################################################
#
if __name__ == '__main__' :
    print ('Run combinatortest.py for unit tests.')

