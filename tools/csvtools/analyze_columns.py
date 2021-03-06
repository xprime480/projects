#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import datetime
import itertools
import math
import sys

import csvprocessor
import dateutils
import texutils
import typeutils


################################################################
#
class Analyzer(csvprocessor.CsvProcessor) :
    """Class which will read CSV files and produce descriptive stats."""

    ################################################################
    #
    def __init__(self, formatter) :
        """Initialize counts."""

        super().__init__()

        self.counts    = {}
        self.nulls     = {}
        self.headers   = None
        self.lines     = 0
        self.formatter = formatter

    ################################################################
    #
    def pre_row_processing(self, hdrs) :
        self._check_headers(hdrs)
        self._init_counts()
        return True

    ################################################################
    #
    def process_row(self, row) :
        """
        Process one row.

        For each column, if the value of the datum is null, update
        the null count, otherwise update the count for the value.
        """

        self.lines += 1
        for h in self.headers :
            v = row[h]
            if not v :
                self.nulls[h] = 1 + self.nulls[h]
            else :
                self.counts[h][v] = 1 + self.counts[h].get(v, 0)

    ################################################################
    #
    def start_write(self) :
        """Write the descriptive statistics for each column."""

        for h in self.headers :
            func, extra = self._get_write_func(h)
            func(h, extra)

        return None

    ################################################################
    #
    def _check_headers(self, hdrs) :
        """Verify that the headers from the current input match previous."""

        if self.headers :
            if self.headers != hdrs :
                print (
                    'Warning: different inputs have different headers.',
                    file=sys.stdout
                )
                
        self.headers = hdrs[:]

    ################################################################
    #
    def _init_counts(self) :
        """Initialze the per-header counts."""

        tmp = {}
        for h in self.headers :
            tmp[h] = {}
        tmp.update(self.counts)
        self.counts = tmp

        tmp = dict(zip(self.headers, itertools.repeat(0)))
        tmp.update(self.nulls)
        self.nulls = tmp

    ################################################################
    #
    def _get_write_func(self, h) :
        """Map the header name to a function to write its statistics."""

        data = self.counts[h]

        if not data :
            return self._write_unknown, None

        if typeutils.all_flags(data) :
            return self._write_flag, None

        fmt = dateutils.all_dates(data)
        if fmt :
            return self._write_date, fmt[0]

        if typeutils.all_floats(data) : # integers count
            return self._write_float, None

        if typeutils.all_strings(data) :
            return self._write_string, None
                    
        return self._write_error, None

    ################################################################
    #
    def _write_unknown(self, h, extra) :
        """Write descriptive statistics for a column of unknown type."""

        self.formatter.write_unknown()

    ################################################################
    #
    def _write_string(self, h, extra) :
        """Write descriptive statistics for a column of strings."""

        c  = len(self.counts[h])
        threshold = c // 100

        cv = list(self.counts[h].items())[:10]
        cv.sort(key=lambda x : x[1], reverse=True)
        t  = [v for v in cv if v[1] >= threshold]
        cv = t

        data = {}
        data['distinct_count'] = c
        data['null_count']     = self.nulls[h]
        data['display_values'] = cv

        self.formatter.write_string(h, data)

    ################################################################
    #
    def _write_flag(self, h, extra) :
        """Write descriptive statistics for a column of flags."""

        tv = 0
        fv = 0

        for k,v in self.counts[h].items() :
            if str(k) == '1' :
                tv += v
            else :
                fv += v

        data = {
            'null_count'  : self.nulls[h],
            'true_count'  : tv,
            'false_count' : fv
        }

        self.formatter.write_flag(h, data)

    ################################################################
    #
    def _write_date(self, h, fmt) :
        """Write descriptive statistics for a column of dates."""

        values = [datetime.datetime.strptime(v, fmt) 
                  for v in self.counts[h].keys()]
        
        data = {
            'null_count'  : self.nulls[h],
            'valid_count' : sum(self.counts[h].values()),
            'earliest'    : min(values).strftime(fmt),
            'latest'      : max(values).strftime(fmt),
        }
        
        self.formatter.write_date(h, data)

    ################################################################
    #
    def _write_float(self, h, extra) :
        """Write descriptive statistics for a column of numerical input."""

        values = []
        for n,c in self.counts[h].items() :
            values.extend([float(n)] * c)

        values.sort()
        size = len(values)

        v = [values[min(size-1, (x * size) // 4)] for x in range(5)]

        avg = sum(values) / size
        tmp = [x-avg for x in values]
        sd  = 0
        if size > 1 :
            sd  = math.sqrt(sum([x * x for x in tmp]) / (size-1))

        c  = len(values)

        data = {
            'value_count' : c,
            'null_count'  : self.nulls[h],
            'quartiles'   : v,
            'avg'         : avg,
            'sd'          : sd
        }

        self.formatter.write_float(h, data)

    ################################################################
    #
    def _write_error(self, h, extra) :
        """Write an error message."""

        self.formatter.write_error(h)

################################################################
#
def main() :
    """Read inputs and analyze columns."""

    parser = argparse.ArgumentParser()
    parser.add_argument("--format",
                        default="latex",
                        help="Stat output format (latex or text)",
                        nargs='?')
    parser.add_argument("files",
                        help="CSV input files",
                        nargs=argparse.REMAINDER)


    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)


    if args.format == 'text' :
        from textformatter import TextFormatter
        formatter = TextFormatter()
    else :
        from latexformatter import LatexFormatter
        formatter = LatexFormatter()

    analyzer = Analyzer(formatter)
    analyzer.read(*args.files)
    analyzer.write()

################################################################
#
if __name__ == '__main__' :
    main()
