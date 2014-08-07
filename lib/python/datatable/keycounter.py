#!/usr/bin/python3

import argparse
import itertools
import logging
import sys

import csvprocessor
import datatable
import datatable.csv
import datatable.factory
import datatable.selectors

class KeyCounter(object) :

    ################################################################
    #
    def __init__(self, categories, factory) :
        self.categories = categories
        self.inputdata  = None
        self.outputdata = None
        self.cat_values = {}
        self.factory    = factory

        for cat in self.categories :
            self.cat_values[cat] = {}

        self.logger = logging.getLogger('main')

    ################################################################
    #
    def read(self, name) :
        self.inputdata = datatable.csv.read(name, self.factory)

    ################################################################
    #
    def get_aggregators(self) :
        return None

    ################################################################
    #
    def callback(self, _) :
        return True

    ################################################################
    #
    def get_results(self, name='temp') :
        if not self.inputdata :
            return None

        if self.outputdata :
            return self.outputdata

        d = self.inputdata
        c = self.categories

        cc = self.inputdata.get_cols()
        ct = self.inputdata.get_types()
        ct_map = dict(zip(cc, ct))

        k = [(cn, ct_map[cn]) for cn in c]
        f = datatable.selectors.simple_column_selector
        keys = list(itertools.starmap(f, k))
        aggs = self.get_aggregators()

        self.outputdata = self.inputdata.rollup(name, keys, aggs, self.callback)

        return self.outputdata
        
    ################################################################
    #
    def write(self, name) :
        results = self.get_results(name)
        if not results :
            return

        datatable.csv.write(results)

################################################################
#
def main() :
    """Read inputs and analyze columns."""

    parser = argparse.ArgumentParser()
    parser.add_argument("--keys",
                        help="columns to count",
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

    keys = []
    if args.keys :
        keys = args.keys[0].split(',')

    analyzer = KeyCounter(keys)
    analyzer.read(*args.infile)
    analyzer.write(*args.outfile)

################################################################
#
if __name__ == '__main__' :
    main()
