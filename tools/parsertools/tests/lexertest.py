#!/usr/bin/python

import sys
import argparse
import simplelexer
import simpletoken

class LexerTester(object) :
    def __init__(self, fin=sys.stdin, fout=sys.stdout) :
        self.fin   = fin
        self.fout  = fout
        self.lexer = simplelexer.SimpleLexer()
        simpletoken.add_tokens(self.lexer)

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

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

    test = LexerTester(fin=args.infile, fout=args.outfile)
    test.run()
