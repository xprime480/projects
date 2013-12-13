#!/usr/bin/python3

import argparse
import itertools
import logging
import sys

import csvdatatable
import csvprocessor
import datatable
import datatablefactory
import selectors

################################################################
#
class KeyCounter(csvprocessor.CsvProcessor) :

    ################################################################
    #
    def __init__(self, categories, extra_columns = ['Count']) :
        super().__init__()

        self.categories = categories

        self.category_values = {}
        for cat in self.categories :
            self.category_values[cat] = {}

        self.category_count = len(self.categories)

        self.headers = self.categories[:]
        self.headers.extend(extra_columns)

        # input data
        #
        self.all_rows = []

    ################################################################
    #
    def process_row(self, row) :
        self.all_rows.append(row)

        for cat in self.categories :
            value = row[cat]
            self.category_values[cat][value] = 1

    ################################################################
    #
    def start_write(self) :
        return self.headers[:]

    ################################################################
    #
    def get_next_output_row(self) :
        for row in self._generate_rows(self.all_rows, {}, 0) :
            yield row

    ################################################################
    #
    def _generate_rows(self, candidates, output, index) :
        if index < self.category_count :
            for row in self._loop_on_index(candidates, output, index) :
                yield row
        else :
            for row in self.generate_one(candidates, output) :
                yield row

    ################################################################
    #
    def _loop_on_index(self, candidates, output, index) :
        key  = self.categories[index]
        vals = self.category_values[key]
        for val in vals.keys() :
            new_output = {}
            new_output.update(output)
            new_output[key] = val

            new_candidates = [x for x in candidates if x[key] == val]

            for row in self._generate_rows(new_candidates, new_output, index+1) :
                yield row

        new_output = {}
        new_output.update(output)
        new_output[key] = '***All***'
        for row in self._generate_rows(candidates, new_output, index+1) :
            yield row

    ################################################################
    #
    def generate_one(self, candidates, output) :
        output['Count'] = len(candidates)
        yield output

class KeyCounterAlt(object) :

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
        self.inputdata = csvdatatable.read(name, self.factory)

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
    def write(self, name) :
        if not self.inputdata :
            return

        d = self.inputdata
        c = self.categories

        cc = self.inputdata.get_cols()
        ct = self.inputdata.get_types()
        ct_map = dict(zip(cc, ct))

        k = [(cn, ct_map[cn]) for cn in c]
        f = selectors.simple_column_selector
        keys = list(itertools.starmap(f, k))
        aggs = self.get_aggregators()

        self.outputdata = self.inputdata.rollup(name, keys, aggs, self.callback)
        csvdatatable.write(self.outputdata)

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
