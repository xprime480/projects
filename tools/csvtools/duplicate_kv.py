#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import itertools
import sys

import csvprocessor

################################################################
#
class Analyzer(csvprocessor.CsvProcessor) :
    def __init__(self, key, val) :
        super().__init__()

        self.a2m = {}
        self.key = key
        self.val = val

    def process_row(self, row) :
        k = row[self.key]
        v = row[self.val]
        q = self.a2m.get(k, {})
        q.update({v:1})
        self.a2m[k] = q

    def start_write(self) :
        return [self.key, self.val]

    def get_next_output_row(self) :
        for key, value in self.a2m.items() :
            if len(value) > 1 :
                for k,v in value.items() :
                    yield { self.key : key,  self.val : k }


################################################################
#
def main() :
    """Read inputs and find keys with multiple values."""

    parser = argparse.ArgumentParser()
    parser.add_argument("key",
                        help="column name of the KEY",
                        nargs=1)
    parser.add_argument("val",
                        help="column name of the VALUE",
                        nargs=1)
    parser.add_argument("infile",
                        help="CSV input file",
                        nargs=1)
    parser.add_argument("outfile",
                        help="CSV output file",
                        nargs=1)

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)
    
    analyzer = Analyzer(args.key[0], args.val[0])
    analyzer.read(*args.infile)
    analyzer.write(*args.outfile)

################################################################
#
if __name__ == '__main__' :
    main()
