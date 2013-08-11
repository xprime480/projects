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
        minus = SingleCharMatcher('-')
        sign,_,rest = minus.match(input)

        digits = OnePlusMatcher(CharSetMatcher("0123456789"))
        m,o,rest = digits.match(rest)
        if m == None :
            return (m,o,input)

        val = int(m)
        if sign == '-' :
            m = sign + m
            val *= -1
            
        return (m, val, rest)

############################################

class SequenceMatcher(Combinator) :
    def __init__(self, *parsers) :
        self.parsers = parsers

    def match(self, input) :
        m = ""
        rest = input
        for p in self.parsers :
            matched,_,rest = p.match(rest)
            if matched is None :
                return (None,None,input)
            m = m + matched

        return (m, m, rest)

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

if __name__ == '__main__' :
    cx = SingleCharMatcher('x')
    print cx.match("xyz")
    (_,_,rest) = cx.match("xxxxxy")
    print rest

    cy = SingleCharMatcher('y')
    cxy = AnyOfMatcher(cx, cy)

    print cxy.match("xyz")
    print cxy.match("yxz")
    print cxy.match("zyx")

    cxs0 = ZeroPlusMatcher(cx)
    print cxs0.match("xxxxxxxyxxxx")
    print cxs0.match("nonehere")

    cxs1 = OnePlusMatcher(cx)
    print cxs1.match("xxxxxxxyxxxx")
    print cxs1.match("nonehere")

    any = AnyCharMatcher()
    print any.match("abc")
    print any.match("")
    print any.match(None)

    print "================="

    all = ZeroPlusMatcher(any)
    print all.match("abcdef")
    print all.match("")


    digits = CharSetMatcher("0123456789")
    print digits.match("623x")

    num = OnePlusMatcher(digits)
    print num.match("623x")

    ints = IntegerMatcher()
    print ints.match("623x")
    print ints.match("-1234623x")
    print ints.match("--1")

    digits2 = CharRangeMatcher('0', '9')
    print digits2.match("823833xx823")

    alpha = AnyOfMatcher( CharRangeMatcher('a', 'z'),
                          CharRangeMatcher('A', 'Z') )
    print alpha.match("DogBerry")

    keyword = SequenceMatcher(alpha,
                              ZeroPlusMatcher(AnyOfMatcher(alpha, digits2)) )
    print keyword.match("DogBerry99$2")

    sm = StringMatcher("base")
    print sm.match("basecase")
    print sm.match("offbase")

    print type(keyword)
    print keyword.__class__
    print 
