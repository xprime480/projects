#!/usr/bin/env python3

"""Provide tools for ranges of dates, integers, and floats."""

import datetime
import itertools

ifmt = '%Y%m%d'

################################################################
#
def make_date(x, ifmt=ifmt) :
    """Turn a string into a datetime.

    X is a string conveying a date/time combination.
    IFMT is a format string defaulting to %Y%m%d.
    """

    return datetime.datetime.strptime(x, ifmt)

################################################################
#
class DateRange(object) :
    """Create a range of dates."""

    ################################################################
    #
    def __init__(self, start, stop, step=1, fmt=ifmt) :
        """Initialize the date range.

        START is a string in FMT format for the beginning date/time.
        STOP  is a string in FMT format for the ending date/time.
        STEP  is the number of days to advance each value.  Fractional
              days are acceptable, but negative days are not.
        FMT is a format string defaulting to %Y%m%d.

        """

        self.start = make_date(start, fmt)
        self.stop  = make_date(stop,  fmt)
        self.step  = datetime.timedelta(step)
        self.fmt   = fmt

        x = self.start + self.step
        if x <= self.start :
            raise Exception(
                'Going back in time not supported for step = %s'% str(step))

    ################################################################
    #
    def dates(self) :
        """Yield a sequence of dates based on initial arguments."""

        current = self.start
        while current <= self.stop :
            yield current
            current = current + self.step

    ################################################################
    #
    def values(self) :
        """Yield a sequence of dates based on initial arguments."""

        for x in self.dates() :
            yield x

    ################################################################
    #
    def make_gen(self) :
        """Return a function that yields dates when called."""

        return self.dates

################################################################
#
class NumericRange(object) :
    """Range of increasing or decreasing date range."""

    ################################################################
    #
    def __init__(self, start, stop, step, fmt) :
        """Initialize a numeric range.

        START is the first value in the range.
        STOP  is a bound on the last value in the range.  This value
              is not guaranteed to be in the output, if the step takes
              the last value past the end
        STEP  is the amount to increment each value.
        FMT   is a formatting string for the output.

        """

        self.start = start
        self.stop  = stop
        self.step  = step
        self.fmt   = fmt

        if self.step == 0 :
            raise Exception(
                'Range with no step not supported')

    ################################################################
    #
    def values(self) :
        """Yield numeric values based on initial arguments."""

        if self.step > 0 :
            current = self.start
            while current <= self.stop :
                yield self.convert(self.fmt % current)
                current = current + self.step
        else :
            current = self.start
            while current >= self.stop :
                yield self.convert(self.fmt % current)
                current = current + self.step

    ################################################################
    #
    def make_gen(self) :
        """Return a function that yields numbers when called."""
        return self.values()

################################################################
#
class IntRange(NumericRange) :
    """Range of integers."""

    ################################################################
    #
    def __init__(self, start, stop, step=1, fmt='%d') :
        NumericRange.__init__(self, start, stop, step, fmt or '%d')

    ################################################################
    #
    def convert(self, value) :
        return int(value)

################################################################
#
class FloatRange(NumericRange) :
    """Range of floating point numbers."""
    
    ################################################################
    #
    def __init__(self, start, stop, step=1, fmt='%f') :
        NumericRange.__init__(self, start, stop, step, fmt or '%f')

    ################################################################
    #
    def convert(self, value) :
        return float(value)

################################################################
#
def div() :
    """Output a divider."""

    print ('========================')

################################################################
#
def test1() :
    """Test to make a single date."""

    ofmt = '%b %d %Y'
    itxt = '19600117'

    d = make_date(itxt)
    o = d.strftime(ofmt)

    print (o)

################################################################
#
def test2(a, b, c=1) :
    """Test DateRange."""

    dr = DateRange(a, b, c).dates
    for d in dr() :
        print (d)

################################################################
#
def test3() :
    """Test DateRange."""

    names = []
    seqs  = []

    names.append('date_key')
    dr = DateRange('20010101', '20010201', 7, '%Y%m%d')
    seqs.append([x.strftime(dr.fmt) for x in dr.values()])

    names.append('product_key')
    seqs.append(range(1,4))

    for qx in [dict(zip(names, x)) for x in itertools.product(*seqs)] :
        print (qx)

################################################################
#
def test4() :
    """Test FloatRange."""

    print ([x for x in FloatRange(0.1, 1.1,  0.1).values()])
    print ([x for x in FloatRange(1.0, 0.0, -0.1).values()])

################################################################
#
def test() :
    """Execute some tests on the classes in this module."""

    test1()
    div()

    test2('20130101', '20130105')
    div()

    test2('20130101', '20130205', 7)
    div()
    try :
        test2('20130101', '20130205', -1)
    except Exception as e:
        print (str(e))
    div()

    test3()
    div()

    test4()
    div()

################################################################
#
if __name__ == '__main__' :
    test()
