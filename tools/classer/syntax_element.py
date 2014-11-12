#!/usr/bin/python3

import combinator

## syntax element

## general use combinators

whitespace = combinator.CharSetMatcher(' \t')
optional_whitespace = combinator.ZeroPlusMatcher(whitespace)

kwClass = combinator.StringMatcher('class')
kwPublic = combinator.StringMatcher('public')

underscore = combinator.SingleCharMatcher('_')
semicolon = combinator.SingleCharMatcher(';')
colon = combinator.SingleCharMatcher(':')
comma = combinator.SingleCharMatcher(',')
scope = combinator.StringMatcher('::')
right_bracket = combinator.SingleCharMatcher('{')

digits = combinator.CharRangeMatcher('0', '9')
lowercase = combinator.CharRangeMatcher('a', 'z')
uppercase = combinator.CharRangeMatcher('A', 'Z')

class Identifier(combinator.Combinator) :
    def __init__(self) :
        identifier_initial = combinator.AnyOfMatcher(
            underscore, 
            lowercase, 
            uppercase
        )
        identifier_rest = combinator.ZeroPlusMatcher(
            combinator.AnyOfMatcher(
                underscore, 
                lowercase, 
                uppercase,
                digits
            )
        )
        self.parser = combinator.SequenceMatcher(
            identifier_initial, 
            identifier_rest
        )

    def match(self, input) :
        m,os,r = self.parser.match(input)
        if m is None :
            return None,None,input

        return m, seq_to_string(os), r


class IdentifierWithNamespace(combinator.Combinator) :
    def __init__(self) :
        identifier = Identifier()
        self.parser = combinator.ListMatcher(
            identifier,
            scope
        )

    def match(self, input) :
        m,os,r = self.parser.match(input) 
        if m is None :
            return m,os,input

        return m,'::'.join(os),r

class SyntaxElement(object) :
    def __init__(self) :
        self.file = '?'
        self.line = 1

    def __repr__(self) :
        return 'at %s:%d' % (self.file, self.line)

def seq_to_string(seq) :
    str = seq[0] + ''.join(seq[1])
    return str


if __name__ == '__main__' :
    txts = [
        '2',
        'Test',
        'Scope::Test',
        'Nested::Scope::Test',
        'Hanging::Scope::'
    ]

    for p in [Identifier(), IdentifierWithNamespace()] :
        for t in txts :
            m,os,r = p.match(t)
            print ('%s -> %s' % (t, os))
        print ('----------------')
