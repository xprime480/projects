#!/usr/bin/python3

import combinator

## forward declaration

class ForwardDeclaration(SyntaxElement) :
    def __init__(self, name) :
        super().__init__()
        self.name = name

    def __repr__(self) :
        return 'forward declaration %s %s' % (self.name, super().__repr__())
    
class ForwardDeclarationParser(combinator.Combinator) :
    def __init__(self) :
        self.parser = combinator.SequenceMatcher(
            optional_whitespace,
            kwClass,
            optional_whitespace,
            identifier,
            optional_whitespace,
            semicolon
        )

    def match(self, input) :
        m,os,r = self.parser.match(input)
        if m :
            name = syntax_element.seq_to_string(os[3])
            o = ForwardDeclaration(name)
            return m,o,r

        return m,os,r

## class delcaration

###########

class ClassDeclScanner(object) :
    def __init__(self) :
        self.parser = combinator.AnyOfMatcher(
            ForwardDeclarationParser(),
            ClassDeclarationParser()
        )

    def scan(self, input) :
        m,o,r = self.parser.match(input[2])
        if m :
            o.file = input[0]
            o.line = input[1]
            return o
        else :
            return None


######################

if __name__ == '__main__' :
    scanner = ClassDeclScanner()
    
    test_inputs = [
        'class Test;',
        'class Test {};'
    ]
    row = 1;
    for input in test_inputs :
        o = scanner.scan(('test', row, input))
        print('%s ==> %s' % (input, o))
        row = row + 1

