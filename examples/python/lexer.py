#!/usr/bin/env python3

import combinator as pc

operators = [
    "+",
    "-",
    "/",
    "*" ]

keywords = [
    "exp",
    "set",
    "unset"
    ]

class TweedOperator(pc.AnyOfMatcher) :
    def __init__(self) :
        ops = []
        for op in operators :
            ops.append(pc.StringMatcher(op))
        pc.AnyOfMatcher.__init__(self,*ops)

    def match(self, input) :
        m,o,r = pc.AnyOfMatcher.match(self, input)
        if m is not None :
            return (m, 'OP', r)
        return (m,o,r)

    
ops   = TweedOperator()
digit = pc.CharRangeMatcher('0', '9')
lower = pc.CharRangeMatcher('a', 'z')
upper = pc.CharRangeMatcher('A', 'Z')
alpha = pc.AnyOfMatcher(lower, upper)
alnum = pc.AnyOfMatcher(alpha, digit)

class TweedIdentifier(pc.Combinator) :
    def __init__(self) :
        self.matcher = pc.SequenceMatcher(
            alpha,
            pc.ZeroPlusMatcher(
                pc.AnyOfMatcher(
                    alpha,
                    digit
            )))

    def match(self, input) :
        m,o,r = self.matcher.match(input)
        if m is None :
            return (m, o, r)
        else :
            return (m, 'ID', r)

identifier = TweedIdentifier()

class TweedKeyword(pc.Combinator) :
    def match(self, input) :
        m,o,r = identifier.match(input)
        if m is None :
            return (m, o, r)
        if m in keywords :
            return (m, 'KW', r)
        return (None, None, input)

kws = TweedKeyword()

def tokenize(input) :
    wschar = pc.CharSetMatcher(' 	\n\r')
    optws = pc.ZeroPlusMatcher(wschar)
    ints = pc.IntegerMatcher()

    matchers = [kws, ops, identifier, ints]

    rest = input
    while True :
        _,_,rest = optws.match(rest)

        if rest == '' :
            break;

        found = False
        for x in matchers :
            m,o,r = x.match(rest)
            if m is not None :
                yield (m, o)
                rest = r
                found = True
                break

        if not found :
            yield None
            rest = ''
        
if __name__ == '__main__'  :
    print ('Run lexertest.py for test suite')
