#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import itertools
import sys

import csvfileio

def texify(name) :
    return '\\_'.join(name.split('_'))

################################################################
#
class Analyzer(object) :
    def __init__(self, key, val) :
        self.a2m = {}
        self.key = key
        self.val = val
        

    def read(self, *files) :
        for f in files :
            with csvfileio.CsvFileIo(f, False) as rdr :
                self._process(rdr)
                
    def write(self) :
        print (self.key, self.val, sep=',')
        for key, value in self.a2m.items() :
            if len(value) > 1 :
                for k,v in value.items() :
                    print (key, k, sep=',')

    def _process(self, rdr) :
        for row in rdr :
            k = row[self.key]
            v = row[self.val]
            q = self.a2m.get(k, {})
            q.update({v:1})
            self.a2m[k] = q

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
    parser.add_argument("files",
                        help="CSV input files",
                        nargs=argparse.REMAINDER)

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)
    
    analyzer = Analyzer(args.key[0], args.val[0])
    analyzer.read(*args.files)
    analyzer.write()

################################################################
#
if __name__ == '__main__' :
    main()
