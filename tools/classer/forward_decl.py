#!/usr/bin/python3

import combinator
import syntax_element

class ForwardDeclaration(syntax_element.SyntaxElement) :
    def __init__(self, name) :
        super().__init__()
        self.name = name

    def __repr__(self) :
        return 'forward declaration %s %s' % (self.name, super().__repr__())
    
class ForwardDeclarationParser(combinator.Combinator) :
    def __init__(self) :
        self.parser = combinator.SequenceMatcher(
            syntax_element.optional_whitespace,
            syntax_element.kwClass,
            syntax_element.optional_whitespace,
            syntax_element.Identifier(),
            syntax_element.optional_whitespace,
            syntax_element.semicolon
        )

    def match(self, input) :
        m,os,r = self.parser.match(input)
        if m :
            name = os[3]
            o = ForwardDeclaration(name)
            return m,o,r

        return m,os,r
