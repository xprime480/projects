#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import datetime
import itertools
import math
import sys

import apply_rules
import csvfileio
import dateutils
import texutils
import typeutils


################################################################
#
class Analyzer(object) :
    """Class which will read CSV files and produce descriptive stats."""

    ################################################################
    #
    def __init__(self) :
        """Initialize counts."""

        self.counts  = {}
        self.nulls   = {}
        self.headers = None
        self.lines   = 0

    ################################################################
    #
    def read(self, *files) :
        """Read and process each CSV file."""

        for f in files :
            with csvfileio.CsvFileIo(f, False) as rdr :
                self._check_headers(rdr)
                self._init_counts()
                self._process(rdr)

    ################################################################
    #
    def write(self, formatter) :
        """Write the descriptive statistics for each column."""

        for h in self.headers :
            def rule_for_no_data(data) :
                if not data :
                    self._write_unknown(h)
                    return True

            def rule_for_flags(data) :
                if typeutils.all_flags(data) :
                    self._write_flag(h, formatter)
                    return True

            def rule_for_dates(data) :
                fmt = dateutils.all_dates(data)
                if fmt :
                    self._write_date(h, formatter, fmt[0])
                    return True

            def rule_for_floats(data) :
                if typeutils.all_floats(data) : # integers count
                    self._write_float(h, formatter)
                    return True

            def rule_for_strings(data) :
                if typeutils.all_strings(data) :
                    self._write_string(h, formatter)
                    return True
                    
            def last_rule(data) :
                self._write_error(h, formatter)
                return True

            rules = [
                rule_for_no_data,
                rule_for_flags,
                rule_for_dates,
                rule_for_floats,
                rule_for_strings,
                last_rule
            ]
            apply_rules.find_a_matching_rule(self.counts[h], *rules)

    ################################################################
    #
    def _check_headers(self, rdr) :
        """Verify that the headers from the current input match previous."""

        if self.headers :
            if self.headers != rdr.fieldnames:
                print (
                    'Warning: different inputs have different headers.',
                    file=sys.stdout
                )
                
        self.headers = rdr.fieldnames[:]

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
    def _process(self, rdr) :
        """
        Process one row.

        For each column, if the value of the datum is null, update
        the null count, otherwise update the count for the value.
        """

        for row in rdr :
            self.lines += 1

            for h in self.headers :
                v = row[h]
                if not v :
                    self.nulls[h] = 1 + self.nulls[h]
                else :
                    self.counts[h][v] = 1 + self.counts[h].get(v, 0)

    ################################################################
    #
    def _write_unknown(self, h, formatter) :
        """Write descriptive statistics for a column of unknown type."""

        formatter.write_unknown()

    ################################################################
    #
    def _write_string(self, h, formatter) :
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

        formatter.write_string(h, data)

    ################################################################
    #
    def _write_flag(self, h, formatter) :
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

        formatter.write_flag(h, data)

    ################################################################
    #
    def _write_date(self, h, formatter, fmt) :
        """Write descriptive statistics for a column of dates."""

        values = [datetime.datetime.strptime(v, fmt) 
                  for v in self.counts[h].keys()]
        
        data = {
            'null_count'  : self.nulls[h],
            'valid_count' : sum(self.counts[h].values()),
            'earliest'    : min(values).strftime(fmt),
            'latest'      : max(values).strftime(fmt),
        }
        
        formatter.write_date(h, data)

    ################################################################
    #
    def _write_float(self, h, formatter) :
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

        formatter.write_float(h, data)

    ################################################################
    #
    def _write_error(self, h) :
        """Write an error message."""

        formatter.write_error(h)

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

    analyzer = Analyzer()
    analyzer.read(*args.files)

    if args.format == 'text' :
        from textformatter import TextFormatter
        formatter = TextFormatter()
    else :
        from latexformatter import LatexFormatter
        formatter = LatexFormatter()
    analyzer.write(formatter)

################################################################
#
if __name__ == '__main__' :
    main()
