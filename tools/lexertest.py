#!/usr/bin/python

import sys
import argparse
import datagenlexer
import datagentoken
import simplelexer
import simpletoken

class LexerTester(object) :
    def __init__(self, fin=sys.stdin, fout=sys.stdout, simple=False) :
        self.fin   = fin
        self.fout  = fout
        if simple :
            self.lexer = simplelexer.SimpleLexer()
            simpletoken.add_tokens(self.lexer)
        else :
            self.lexer = datagenlexer.DatagenLexer()
            datagentoken.add_tokens(self.lexer)

    def run(self) :
        for line in self.fin :
            self.lexer.add_text(line)
        while True :
            token = self.lexer.get_token()
            if not token :
                break
            self.fout.write('%s\n' % token)
        

if __name__ == '__main__' :
    parser = argparse.ArgumentParser()
    parser.add_argument("infile",
                        help="file full of tokens to test", 
                        default=sys.stdin,
                        nargs='?',
                        type=argparse.FileType('r') )
    parser.add_argument("outfile",
                        help="file to which to write results", 
                        default=sys.stdout,
                        nargs='?',
                        type=argparse.FileType('w') )
    parser.add_argument("--simple",
                        help="test using the simple lexer", 
                        action='store_true' )

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

    test = LexerTester(fin=args.infile, fout=args.outfile, simple=args.simple)
    test.run()
