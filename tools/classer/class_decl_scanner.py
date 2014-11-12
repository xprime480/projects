#!/usr/bin/python3

import combinator

import class_decl
import forward_decl
import syntax_element


## stuff to ignore

class IgnorableParser(object) :
    def __init__(self) :
        ignored = []
        kw_to_ignore = ['template', 'DEFINE_ERROR']
        for kw in kw_to_ignore :
            ignored.append(combinator.StringMatcher(kw))

        self.parser = combinator.SequenceMatcher(
            syntax_element.optional_whitespace,
            combinator.AnyOfMatcher(*ignored)
        )
        
    def match(self, input) :
        m,o,r = self.parser.match(input)
        if m is not None :
            return m,syntax_element.SyntaxElement(),r
        return None,None,input
    
###########

class ClassDeclScanner(object) :
    def __init__(self) :
        self.parser = combinator.AnyOfMatcher(
            forward_decl.ForwardDeclarationParser(),
            class_decl.ClassDeclarationParser(),
            IgnorableParser()
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
    
    scanner.scan((
        'debug', 
        1, 
        'template <class X> X * foo() { return 0; }'
    ))
    
    test_inputs = [
        'class Test;',
        'class Test {};',
        'class Test : public One {};',
        'class Test : public One, public Too {};',
        'template <class X> X * foo() { return 0; }'
    ]
    row = 1;
    for input in test_inputs :
        o = scanner.scan(('test', row, input))
        print('%s ==> %s' % (input, o))
        row = row + 1

