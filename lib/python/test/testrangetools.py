#!/usr/bin/env python3

import unittest

import rangetools

##################################################################
#
class RangeToolsTest(unittest.TestCase) :
    """Test the Range tools."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        unittest.TestCase.__init__(self, n)

    ##################################################################
    #
    def test_single_date_format(self) :
        """Test that reading and writing the date works."""

        ofmt = '%b %d %Y'
        itxt = '19600117'

        d = rangetools.make_date(itxt)
        o = d.strftime(ofmt)

        self.assertEqual('Jan 17 1960', o)

    ################################################################
    #
    def test_date_range(self) :
        """Test DateRange."""

        dr = rangetools.DateRange('20130101', '20130105', 1)
        ds = [d for d in dr.dates()]
        self.assertEqual(5, len(ds))
        
        fmt = '%Y%m%d'
        self.assertEqual('20130101', ds[ 0].strftime(fmt))
        self.assertEqual('20130105', ds[-1].strftime(fmt))

    ################################################################
    #
    def test_date_range_values(self) :
        """Test DateRange values function."""

        dr = rangetools.DateRange('20130101', '20130105', 1)
        ds = [d for d in dr.values()]
        self.assertEqual(5, len(ds))
        
        fmt = '%Y%m%d'
        self.assertEqual('20130101', ds[ 0].strftime(fmt))
        self.assertEqual('20130105', ds[-1].strftime(fmt))

    ################################################################
    #
    def test_date_range_weekly(self) :
        """Test DateRange skipping by 7 days."""

        dr = rangetools.DateRange('20130101', '20130105', 7)
        ds = [d for d in dr.values()]
        self.assertEqual(1, len(ds))
        
        fmt = '%Y%m%d'
        self.assertEqual('20130101', ds[ 0].strftime(fmt))

    ################################################################
    #
    def test_date_range_error(self) :
        """Test DateRange with invalid constructor arguments."""

        with self.assertRaises(Exception) :
            dr = rangetools.DateRange('20130101', '20130105', -1)

    ################################################################
    #
    def test_integer_range_up(self) :
        """Test IntRange."""

        jr = rangetools.IntRange(1, 4)
        js = [j for j in jr.values()]
        self.assertEqual(4, len(js))
        
        self.assertEqual(1, js[ 0])
        self.assertEqual(4, js[-1])

    ################################################################
    #
    def test_integer_range_up_skip(self) :
        """Test IntRange skipping some values."""

        jr = rangetools.IntRange(1, 4, 2)
        js = [j for j in jr.values()]
        self.assertEqual(2, len(js))
        
        self.assertEqual(1, js[ 0])
        self.assertEqual(3, js[-1])

    ################################################################
    #
    def test_integer_down(self) :
        """Test IntRange going down."""

        jr = rangetools.IntRange(4, 1, -1)
        js = [j for j in jr.values()]
        self.assertEqual(4, len(js))
        
        self.assertEqual(4, js[ 0])
        self.assertEqual(1, js[-1])

    ################################################################
    #
    def test_integer_range_down_skip(self) :
        """Test IntRange going down skipping some values."""

        jr = rangetools.IntRange(4, 1, -2)
        js = [j for j in jr.values()]
        self.assertEqual(2, len(js))
        
        self.assertEqual(4, js[ 0])
        self.assertEqual(2, js[-1])

    ################################################################
    #
    def test_integer_range_error(self) :
        """Test IntRange with invalid constructor arguments."""

        with self.assertRaises(Exception) :
            js = rangetools.IntRange(1, 1, 0)


    ################################################################
    #
    def test_float_range_up(self) :
        """Test FloatRange."""

        jr = rangetools.FloatRange(1.0, 4.0)
        js = [j for j in jr.values()]
        self.assertEqual(4, len(js))
        
        self.assertEqual(1.0, js[ 0])
        self.assertEqual(4.0, js[-1])

    ################################################################
    #
    def test_float_range_up_large(self) :
        """Test FloatRange with larger than unit step."""

        jr = rangetools.FloatRange(1.0, 4.0, 2.0)
        js = [j for j in jr.values()]
        self.assertEqual(2, len(js))
        
        self.assertEqual(1.0, js[ 0])
        self.assertEqual(3.0, js[-1])

    ################################################################
    #
    def test_float_range_up_small(self) :
        """Test FloatRange with smaller than unit step."""

        jr = rangetools.FloatRange(1.0, 4.0, 1.0/3.0)
        js = [j for j in jr.values()]
        self.assertEqual(10, len(js))
        
        self.assertEqual(1.0, js[ 0])
        self.assertEqual(4.0, js[-1])

    ################################################################
    #
    def test_float_down(self) :
        """Test FloatRange going down."""

        jr = rangetools.FloatRange(4.0, 1.0, -1.0)
        js = [j for j in jr.values()]
        self.assertEqual(4, len(js))
        
        self.assertEqual(4.0, js[ 0])
        self.assertEqual(1.0, js[-1])

    ################################################################
    #
    def test_float_range_down_large(self) :
        """Test FloatRange going down with larger than unit step."""

        jr = rangetools.FloatRange(4.0, 1.0, -2.0)
        js = [j for j in jr.values()]
        self.assertEqual(2, len(js))
        
        self.assertEqual(4.0, js[ 0])
        self.assertEqual(2.0, js[-1])

    ################################################################
    #
    def test_float_range_down_small(self) :
        """Test FloatRange going down with smaller than unit step."""

        jr = rangetools.FloatRange(4.0, 1.0, -0.5)
        js = [j for j in jr.values()]
        self.assertEqual(7, len(js))
        
        self.assertEqual(4.0, js[ 0])
        self.assertEqual(1.0, js[-1])

    ################################################################
    #
    def test_float_range_error(self) :
        """Test FloatRange with invalid constructor arguments."""

        with self.assertRaises(Exception) :
            js = rangetools.FloatRange(1.0, 1.0, 0.0)


    ################################################################
    #
    def test_pairs(self) :
        """Test generation of pairs."""

        ps = [p for p in rangetools.pairs(0)]
        self.assertEqual([], ps)

        ps = [p for p in rangetools.pairs(2)]
        self.assertEqual([(1,2)], ps)

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
