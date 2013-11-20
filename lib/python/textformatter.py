#!/usr/bin/python3

from columnformatter import ColumnFormatter

################################################################
#
class TextFormatter(ColumnFormatter) :

    ################################################################
    #
    def write_string(self, name, data) :
        print ()
        print ('Column "%s" has %d distinct values and %d NULL values.' %
               (name, data['distinct_count'], data['null_count']))

        cs = len(data['display_values'])
        if not cs :
            print ('No value accounts for more than 1% of the values.')
            return

        print ('Top %d values for "%s"' % (cs, name))
        print ('%32s %8s' % ('Value', 'Count'))
        print ('%32s %8s' % ('=' * 32, '=' * 5))
        for p in data['display_values'] :
            print ('%32s %8s' % p)

    ################################################################
    #
    def write_flag(self, name, data) :
        print ()
        print ('Column "%s" contains flags with %d true, %d false and %d NULL values.' %
               (name, data['true_count'], data['false_count'], data['null_count']))
        
    ################################################################
    #
    def write_date(self, name, data) :
        print ()
        print ('Column "%s" contains dates with %d valid and %d NULL values.' %
               (name, data['valid_count'], data['null_count']))
        print ('Date range is from %s to %s.' % (data['earliest'], data['latest']))

    ################################################################
    #
    def write_float(self, name, data) :
        print ()
        print ('Column "%s" has %d numeric and %d NULL values' %
               (name, data['value_count'], data['null_count']))


        print ('Statistics for "%s"' % (name))
        print ('Quartiles: ')
        print ('%.2f %.2f %.2f %.2f %.2f ' % tuple(data['quartiles']))
        print ('Average: %.2f \tStd Dev: %.2f' % (data['avg'], data['sd']))

