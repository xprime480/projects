#!/usr/bin/python3

import combinator

import class_decl
import forward_decl


## class delcaration

###########

class ClassDeclScanner(object) :
    def __init__(self) :
        self.parser = combinator.AnyOfMatcher(
            forward_decl.ForwardDeclarationParser(),
            class_decl.ClassDeclarationParser()
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
        'class Test {};',
        'class Test : public One {};',
        'class Test : public One, public Too {};'
    ]
    row = 1;
    for input in test_inputs :
        o = scanner.scan(('test', row, input))
        print('%s ==> %s' % (input, o))
        row = row + 1

