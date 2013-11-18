#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import itertools
import math
import sys

import csvfileio

def texify(name) :
    t = '\\_'.join(name.split('_'))
    t = '\\#'.join(t.split('#'))
    return t

def likely_date(v) :
    """Check if input is likely a date."""

    if int(v) != v :
        return False
    y = v // 10000
    if y < 1900 or y > 2200 :
        return False
    m = (v // 100) % 100
    if m < 1 or m > 12 :
        return False
    d = v % 100
    if d < 1 or d > 31 :
        return False

    return True

def likely_flag(v) :
    return v == 1 or v == 0 or v == '1' or v == '0'


################################################################
#
class ColumnFormatter(object) :

    def write_string(self, name, data) :
        pass

    def write_unknown(self) :
        pass

    def write_error(self, name) :
        print ('Error in field', name)

################################################################
#
class LatexFormatter(ColumnFormatter) :
    pass

    def write_string(self, name, data) :
        th = texify(name)

        print ('\\item[%s] has %d distinct values and %d NULL values.' %
               (th, data['distinct_count'], data['null_count']))

        cs = len(data['display_values'])
        if not cs :
            print ('No value accounts for more than 1\\% of the values.')
            return

        tn = 'tab:' + ''.join(name.split('_'))

        print ('See Table \\ref{%s}' % (tn))

        print ('\\begin{table}')
        print ('\\caption{Top %d values for %s} \\label{%s}' % (cs, th, tn))
        print ('\centering')
        print ('\\begin{tabular}{|r|l|}')
        print ('\\hline')
        print ('Value & Count \\\\')
        print ('\\hline')
        for p in data['display_values'] :
            print ('%s & %s \\\\' % p)
        print ('\\hline')
        print ('\\end{tabular}')
        print ('\\end{table}')

    def write_float(self, name, data) :
        th = texify(name)
        x = ''.join(name.split('_'))
        x = ''.join(x.split('#'))
        tn = 'tab:' + x

        print ('\\item[%s] has %d numeric and %d NULL values' %
               (th, data['value_count'], data['null_count']))
        print ('See Table \\ref{%s}' % (tn))

        print ('\\begin{table}[ht]')
        print ('\\caption{Statistics for %s} \\label{%s}' % (th, tn))
        print ('\centering')
        print ('\\begin{tabular}{|rrrrr|}')
        print ('\\hline')
        print ('Quartiles & & & &  \\\\')
        print ('%.2f & %.2f & %.2f & %.2f & %.2f \\\\' % tuple(data['quartiles']))
        print ('\\hline')
        print ('Average & %.2f & & Std Dev & %.2f \\\\' % (data['avg'], data['sd']))
        print ('\\hline')
        print ('\\end{tabular}')
        print ('\\end{table}')

    def write_error(self, name) :
        h = texify(name)
        print ('\\item[%s] was not processed correctly, please report' % (h,))

################################################################
#
class Analyzer(object) :
    def __init__(self) :
        self.counts  = {}
        self.nulls   = {}
        self.headers = None
        self.lines   = 0
        self.types   = {}

    def read(self, *files) :
        for f in files :
            with csvfileio.CsvFileIo(f, False) as rdr :
                self._check_headers(rdr)
                self._init_counts()
                self._process(rdr)

    def write(self, formatter) :
        for h in self.headers :
            if self.types[h] == self._proc_unknown_type :
                self._write_unknown(h, formatter)
            elif self.types[h] == self._proc_string :
                self._write_string(h, formatter)
            elif self.types[h] == self._proc_float :
                self._write_float(h, formatter)
            else :
                self._write_error(h, formatter)

    def _check_headers(self, rdr) :
        if self.headers :
            if self.headers != rdr.fieldnames:
                print ('Warning: different inputs have different headers.')

        self.headers = rdr.fieldnames[:]
        for h in self.headers :
            self.types[h] = self._proc_unknown_type

    def _init_counts(self) :

        tmp = {}
        for h in self.headers :
            tmp[h] = {}
        tmp.update(self.counts)
        self.counts = tmp

        tmp = dict(zip(self.headers, itertools.repeat(0)))
        tmp.update(self.nulls)
        self.nulls = tmp

    def _process(self, rdr) :
        for row in rdr :
            self.lines += 1

            for h in self.headers :
                v = row[h]
                self.types[h](h,v)

    def _proc_null(self, h) :
        self.nulls[h] = 1 + self.nulls[h]

    def _proc_unknown_type(self, h, v) :
        if not v :
            self._proc_null(h)
            return

        try :
            v2 = float(v)
            self.types[h] = self._proc_float
            self.counts[h] = []
        except :
            self.types[h] = self._proc_string

        self.types[h](h, v)

    def _proc_float(self, h, v) :
        if not v :
            self._proc_null(h)
            return

        v = float(v)
        self.counts[h].append(v)

    def _proc_string(self, h, v) :
        if not v :
            self._proc_null(h)
            return

        self.counts[h][v] = 1 + self.counts[h].get(v, 0)

    def _write_unknown(self, h, formatter) :
        formatter.write_unknown()

    def _write_string(self, h, formatter) :

        th = texify(h)
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

    def _write_float(self, h, formatter) :
        values = self.counts[h]

        # the following code is horrible
        # find a pythonic way to fix it.

        flag = True
        for x in values :
            if not likely_date(x) :
                flag = False
                break
        if flag :
            self._write_as_string(h)
            return

        flag = True
        for x in values :
            if not likely_flag(x) :
                flag = False
                break
        if flag :
            self._write_as_string(h)
            return

        values.sort()
        size = len(values)

        v = [values[min(size-1, (x * size) // 4)] for x in range(5)]

        avg = sum(values) / size
        tmp = [x-avg for x in values]
        sd  = 0
        if size > 1 :
            sd  = math.sqrt(sum([x * x for x in tmp]) / (size-1))

        c  = len(self.counts[h])

        data = {
            'value_count' : c,
            'null_count'  : self.nulls[h],
            'quartiles'   : v,
            'avg'         : avg,
            'sd'          : sd
        }

        formatter.write_float(h, data)

    def _write_as_string(self, h) :
        values = self.counts[h]
        self.counts[h] = {}
        for v in values :
            self._proc_string(h, str(int(v)))

        self._write_string(h)

    def _write_error(self, h) :
        formatter.write_error(h)

################################################################
#
def main() :
    """Read inputs and analyze columns."""

    parser = argparse.ArgumentParser()
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

    formatter = LatexFormatter()
    analyzer.write(formatter)

################################################################
#
if __name__ == '__main__' :
    main()
