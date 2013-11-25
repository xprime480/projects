#!/usr/bin/python3

import argparse
import itertools
import sys

import csvdatatable
import csvprocessor
import datatable
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
    def __init__(self, categories) :
        self.categories = categories
        self.inputdata  = None
        self.outputdata = None
        self.cat_values = {}

        for cat in self.categories :
            self.cat_values[cat] = {}

    ################################################################
    #
    def read(self, name) :
        self.inputdata = csvdatatable.read(name)

    ################################################################
    #
    def generate_counts(self, name='temp') :
        # get the unique keys for each column
        for cat in self.categories :
            selector = selectors.simple_column_selector(cat)
            self.cat_values[cat] = self.inputdata.group_by('temp', [selector]).get_values(cat)
            self.cat_values[cat].append('***All***')
        del (selector)

        # create the output table
        aggs = self.get_aggregators()
        cols = self.categories[:]
        cols.extend([a.get_name() for a in aggs])
        self.outputdata = datatable.DataTable(name, cols)
        del (cols)
        
        # get counts for each combination.
        for x in itertools.product(*[v for v in self.cat_values.values()]) :
            filterfn = self._make_filter_fn(x)
            dt = self.inputdata.filter('temp', filterfn)
            row = list(x)[:]
            row.extend([a(dt) for a in aggs])
            self.outputdata.add_row(row)

        del (aggs)

    ################################################################
    #
    def get_aggregators(self) :
        return [selectors.count_aggregator()]

    ################################################################
    #
    def write(self, name) :
        if not self.inputdata :
            return

        if not self.outputdata :
            self.generate_counts(name)

        csvdatatable.write(self.outputdata)

    ################################################################
    #
    def  _make_filter_fn(self, values) :
        named = zip(self.categories, values)
        preds = [v for v in named if v[1] != '***All***']
        def ffn(row) :
            return all([row[p[0]] == p[1] for p in preds])
        return ffn

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
