#!/usr/bin/python3

import combinator
import syntax_element

class ClassDeclaration(syntax_element.SyntaxElement) :
    def __init__(self, name) :
        super().__init__()
        self.name = name
        self.bases = []

    def add_base(self, base) :
        self.bases.append(base)

    def __repr__(self) :
        return 'class declaration %s%s %s' % (self.name, self.repr_bases(), super().__repr__())

    def repr_bases(self) :
        if len(self.bases) == 0 :
            return ''

        if len(self.bases) == 1 :
            return ' with base %s' % self.bases[0]

        return ' with bases %s' % ', '.join(self.bases)

class BaseListParser(combinator.Combinator) :
    def __init__(self) :
        sep_parser = combinator.SequenceMatcher(
            syntax_element.optional_whitespace,
            syntax_element.comma
        )
        item_parser = combinator.SequenceMatcher(
            syntax_element.optional_whitespace,
            syntax_element.kwPublic,
            syntax_element.optional_whitespace,
            syntax_element.IdentifierWithNamespace()
        )
        self.parser = combinator.ZeroOneMatcher(
            combinator.SequenceMatcher(
                syntax_element.optional_whitespace,
                syntax_element.colon,
                combinator.ListMatcher(item_parser, sep_parser)
            )
        )

    def match(self, input) :
        m,os,r = self.parser.match(input)
        if not m :
            return '',[],input
        
        os = [x[3] for x in os[2]]
        return m,os,r

class ClassDeclarationParser(combinator.Combinator) :
    def __init__(self) :
        bases = BaseListParser()

        self.parser = combinator.SequenceMatcher(
            syntax_element.optional_whitespace,
            syntax_element.kwClass,
            syntax_element.optional_whitespace,
            syntax_element.Identifier(),
            bases,
            syntax_element.optional_whitespace,
            syntax_element.right_bracket
        )

    def match(self, input) :
        m,os,r = self.parser.match(input)
        if m : 
            name = os[3]
            o = ClassDeclaration(name)
            for b in os[4] :
                o.add_base(b)
            return m,o,r

        return m,os,r

if __name__ == '__main__' :
    b = BaseListParser()
    b_txt = [
        '{};',
        ': public First {};',
        ': public First, public Second {};'
    ]
    for txt in b_txt :
        print ('%s -> %s' % (txt, b.match(txt)[1]))
        
    d = ClassDeclarationParser()
    d_txt = [
        'class Test {};',
        'class Test : public First {};',
        'class Test : public First, public Second {};',
        'class Test : public ns::First {};',
    ]
    for txt in d_txt :
        print ('%s -> %s' % (txt, d.match(txt)[1]))
        
