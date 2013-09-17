#!/usr/bin/env python3

import unittest\

from verscmp import *

class TestVersCmp( unittest.TestCase ) :
    """Tests for the verscmp function"""

    def setUp( self ) :
        """create various version strings (and some bogus ones)"""

        self.v1 = '1'
        self.v10 = '1.0'
        self.v20 = '2.0'
        self.v11 = '1.1'
        self.v111 = '1.1.1'
        self.v12  = '1.2'
        self.vbig = '1000.0'
        self.nv1 = 'x'

    def test_no_dot( self ) :
        """Compare a version with no dots"""

        self.assertEqual( -1, verscmp( self.v1, self.v11 ) )

    def test_strip_zeros( self ) :
        """Compare version that differ only in trailing zeros"""

        self.assertEqual( 0, verscmp( self.v1, self.v10 ) )

    def test_same_len_lt( self ) :
        """Compare versions of same length where first < second"""

        self.assertEqual( -1, verscmp( self.v10, self.v20 ) )

    def test_same_len_eq( self ) :
        """Compare versions of same length where first == second"""

        self.assertEqual( 0, verscmp( self.v111, self.v111 ) )

    def test_same_len_gt( self ) :
        """Compare versions of same length where first > second"""

        self.assertEqual( 1, verscmp( self.v20, self.v10 ) )

    def test_diff_len_lt( self ) :
        """Compare versions of different length where first < second"""

        self.assertEqual( -1, verscmp( self.v111, self.v12 ) )

    def test_diff_len_gt( self ) :
        """Compare versions of different length where first > second"""

        self.assertEqual( 1, verscmp( self.v111, self.v10 ) )

    def test_diff_one_bad( self ) :
        """Compare valid version to invalid version"""

        self.assertRaises( ValueError, verscmp, self.nv1, self.v10 )

    def test_big_order( self ) :
        """ensure that ordering is really numeric, not string sort"""

        self.assertEqual( -1, verscmp( self.v20, self.vbig ) )

    def test_sort( self ) :
        """ensure that verscmp works correctly with sort"""

        t = [ self.v1, self.v10, self.v20, self.v11, self.v111,
              self.v12, self.vbig ]
        t.sort( key=components )
        for i in range( len( t ) - 2 ) :
            self.assertNotEqual( 1, verscmp( t[ i ], t[ i+1 ] ) )


if '__main__' == __name__ :
    unittest.main()
