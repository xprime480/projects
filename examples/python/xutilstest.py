#!/usr/bin/env python

from xutils import *
import unittest

class TestConvertEntity(unittest.TestCase) :
    def test_null_conversion(self) :
        """Test the null case"""
        str = ''
        self.assertEqual(str, convertEntity(str))

    def test_constant_conversion(self) :
        """Test the case of a string with no entities"""
        str = 'nothing'
        self.assertEqual(str, convertEntity(str))
        
    def test_basic_conversion(self) :
        """Test the case consisting of exactly one entity"""
        strIn  = '&amp;'
        strOut = '&'
        self.assertEqual(strOut, convertEntity(strIn))

    def test_consecutive_conversion(self) :
        """Test the case of several consecutive entities."""
        strIn  = '&lt;&amp;&gt;'
        strOut = '<&>'
        self.assertEqual(strOut, convertEntity(strIn))

    def test_false_prefix(self) :
        """Test the case of a 'false prefix'"""
        strIn  = '&lt&amp;&gt;'
        strOut = '&lt&>'
        self.assertEqual(strOut, convertEntity(strIn))

    def test_initial_semi(self) :
        """Test the case of a semicolon before any ampersand"""
        strIn  = 'xx ;dog&amp;'
        strOut = 'xx ;dog&'
        self.assertEqual(strOut, convertEntity(strIn))

    def test_false_entity(self) :
        """Test the case of an apparant entity that is undefined"""
        str  = 'prefix &false; suffix'
        self.assertEqual(str, convertEntity(str))

class TestBeautifulSoup(unittest.TestCase) :
    def test_bs(self) :
        """Just test something"""
        self.assertEqual(1,1)

class TestOpenAnything(unittest.TestCase) :
    def test_open_file(self) :
        """Open a file and get its length"""
        f = 'xutilstest.py'
        l = len(open(f).read())
        self.assertEqual(l, len(open_anything(f).read()))

    def test_open_url(self) :
        """Open a url and get its length"""
        f = 'http://khizilla'
        p = 'DOCTYPE'
        self.assertEqual(p, open_anything(f).read(9)[2:])

    def test_open_string(self) :
        """Open a string and get back the same"""
        s = 'Lousy test string'
        self.assertEqual(s, open_anything(s).read())

if '__main__' == __name__ :
    unittest.main()
