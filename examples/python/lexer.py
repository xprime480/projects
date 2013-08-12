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

identifier = pc.SequenceMatcher(alpha,
                                pc.ZeroPlusMatcher(pc.AnyOfMatcher(alpha,
                                                                   digit)) )


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

    rest = input
    while True :
        _,_,rest = optws.match(rest)

        if rest == '' :
            break;
        
        m,o,r = kws.match(rest)
        if m is not None :
            yield (m,o)
            rest = r
        else :
            m,o,r = ops.match(rest)
            if m is not None :
                yield (m,o)
                rest = r
            else :
                m,_,r = identifier.match(rest)
                if m is not None :
                    yield (m,'ID')
                    rest = r
                else :
                    m,o,r = ints.match(rest)
                    if m is not None :
                        yield (m,o)
                        rest = r
                    else :
                        print('Cannot tokenize: ', rest)
                        break

    return


if __name__ == '__main__'  :
    print(ops.match("+"))
    print(kws.match("set"))
    print(kws.match("settle"))
    print(list(tokenize("")))
    print(list(tokenize("2+2")))
    print(list(tokenize("exp 3 5")))
    print(list(tokenize("dogfish99")))
    print(list(tokenize("...")))
