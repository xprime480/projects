#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import sys

import csvfileio

def texify(name) :
    return '\\_'.join(name.split('_'))

################################################################
#
class Analyzer(object) :
    def __init__(self, key1, key2) :
        self.equal = 0
        self.total = 0
        self.key1  = key1
        self.key2  = key2
        
    def read(self, *files) :
        for f in files :
            with csvfileio.CsvFileIo(f, False) as rdr :
                self._process(rdr)
                
    def write(self) :
        pct = 100.0 * (float(self.equal) / float(self.total))
        print ('%d of %d rows equal (%6.2f%%)' % (self.equal, self.total, pct))

    def _process(self, rdr) :
        for row in rdr :
            self.total += 1
            k1 = row[self.key1]
            k2 = row[self.key2]
            if k1 == k2 :
                self.equal += 1

################################################################
#
def main() :
    """Read inputs and find keys with multiple values."""

    parser = argparse.ArgumentParser()
    parser.add_argument("key1",
                        help="KEY name of first column to compare",
                        nargs=1)
    parser.add_argument("key2", 
                        help="KEY name of second column to compare",
                        nargs=1)
    parser.add_argument("files",
                        help="CSV input files",
                        nargs=argparse.REMAINDER)
    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)
    
    analyzer = Analyzer(args.key1[0], args.key2[0])
    analyzer.read(*args.files)
    analyzer.write()

################################################################
#
if __name__ == '__main__' :
    main()
