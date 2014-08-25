#!/usr/bin/python3

import operator
import unittest

import DicePdf
import PdfUtils

class TestDicePdf(unittest.TestCase) :
    def test_merge_default(self) :
        pdfIn  = DicePdf.DicePdf("d2").get()
        pdfOut = PdfUtils.merge(pdfIn, pdfIn)
        self.assertFalse(0 in pdfOut.keys())
        self.assertFalse(1 in pdfOut.keys())
        self.assertEqual(pdfOut[2], 0.25)
        self.assertEqual(pdfOut[3], 0.50)
        self.assertEqual(pdfOut[4], 0.25)
        self.assertFalse(5 in pdfOut.keys())

    def test_merge_max(self) :
        pdfIn  = DicePdf.DicePdf("d2").get()
        pdfOut = PdfUtils.merge(pdfIn, pdfIn, max)
        self.assertFalse(0 in pdfOut.keys())
        self.assertEqual(pdfOut[1], 0.25)
        self.assertEqual(pdfOut[2], 0.75)
        self.assertFalse(3 in pdfOut.keys())

    def test_mean_d2(self) :
        pdfIn  = DicePdf.DicePdf("d2").get()
        self.assertEqual(PdfUtils.mean(pdfIn), 1.5)

    def test_mean_3d6p1(self) :
        pdfIn  = DicePdf.DicePdf("3d6+1").get()
        self.assertEqual(PdfUtils.mean(pdfIn), 11.5)

    def test_variance_d2(self) :
        pdfIn  = DicePdf.DicePdf("d2").get()
        self.assertEqual(PdfUtils.variance(pdfIn), 0.25)

    def test_variance_3d6p1(self) :
        pdfIn  = DicePdf.DicePdf("3d6+1").get()
        self.assertEqual(round(PdfUtils.variance(pdfIn), 5), 8.75)

if __name__ == '__main__':
    unittest.main()
