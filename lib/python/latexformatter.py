#!/usr/bin/python3

import texutils

from columnformatter import ColumnFormatter

################################################################
#
class LatexFormatter(ColumnFormatter) :

    ################################################################
    #
    def write_string(self, name, data) :
        th = texutils.texify(name)

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

    ################################################################
    #
    def write_flag(self, name, data) :
        th = texutils.texify(name)

        print ('\\item[%s] contains flags with %d true, %d false and %d NULL values.' %
               (th, data['true_count'], data['false_count'], data['null_count']))
    ################################################################
    #
    def write_date(self, name, data) :
        th = texutils.texify(name)

        print ()
        print ('\\item[%s] contains dates with %d valid and %d NULL values.' %
               (th, data['valid_count'], data['null_count']))
        print ('Date range is from %s to %s.' % (data['earliest'], data['latest']))

    ################################################################
    #
    def write_float(self, name, data) :
        th = texutils.texify(name)
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

    ################################################################
    #
    def write_error(self, name) :
        h = texutils.texify(name)
        print ('\\item[%s] was not processed correctly, please report' % (h,))
