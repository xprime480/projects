#!/usr/bin/python3

import unittest

import DicePdf
import SpecParser

class TestDicePdf(unittest.TestCase) :
    def test_(self) :
        pdf = DicePdf.DicePdf()
        self.assertEqual(pdf.p(0), 0.0)
        self.assertEqual(pdf.p(1), 1.0/6)

    def test_d6(self) :
        pdf = DicePdf.DicePdf("d6")
        self.assertEqual(pdf.p(0), 0.0)
        self.assertEqual(pdf.p(1), 1.0/6)

    def test_d4(self) :
        pdf = DicePdf.DicePdf("d4")
        self.assertEqual(pdf.p(0), 0.0)
        self.assertEqual(pdf.p(1), 1.0/4)

    def test_d4p1(self) :
        pdf = DicePdf.DicePdf("d4+1")
        self.assertEqual(pdf.p(0), 0.0)
        self.assertEqual(pdf.p(1), 0.0)
        for x in range(2,6) :
            self.assertEqual(pdf.p(x), 0.25)

    def test_3d2m1(self) :
        pdf = DicePdf.DicePdf("3d2-1")
        self.assertEqual(pdf.p(0), 0.0)
        self.assertEqual(pdf.p(1), 0.0)
        self.assertEqual(pdf.p(2), 1.0/8)
        self.assertEqual(pdf.p(3), 3.0/8)
        self.assertEqual(pdf.p(4), 3.0/8)
        self.assertEqual(pdf.p(5), 1.0/8)
        self.assertEqual(pdf.p(6), 0.0)

    def test_merge_1(self) :
        pdf = DicePdf.DicePdf()
        p1 = dict([(1 , 1.0)])
        p  = pdf.merge_pdfs(p1, p1)
        self.assertEqual(p[2], 1.0)

    def test_merge_2(self) :
        pdf = DicePdf.DicePdf()
        p1 = dict([(1 , 1.0)])
        p2 = dict([(1 , 0.5), (2, 0.5)])
        p  = pdf.merge_pdfs(p1, p2)
        self.assertEqual(p[2], 0.5)

    def test_single_die_1(self) :
        pdf = DicePdf.DicePdf()
        p = pdf.make_single_die_pdf(3)
        for x in range(3) :
            self.assertEqual(p[x+1], 1.0/3)

    def test_merge_3(self) :
        pdf = DicePdf.DicePdf()
        p2 = pdf.make_single_die_pdf(2)
        p  = pdf.merge_pdfs(p2, p2)
        self.assertFalse(1 in p.keys())
        self.assertEqual(p[2], 0.25)
        self.assertEqual(p[3], 0.50)
        self.assertEqual(p[4], 0.25)
        
    def test_merge_4(self) :
        pdf = DicePdf.DicePdf()
        p1 = pdf.make_single_die_pdf(1)
        p2 = pdf.make_single_die_pdf(2)
        p  = pdf.merge_pdfs(p1, p2)
        self.assertFalse(1 in p.keys())
        self.assertEqual(p[2], 0.50)
        self.assertEqual(p[3], 0.50)
        self.assertFalse(4 in p.keys())

    def test_base_probs_1(self) :
        parser = SpecParser.SpecParser()
        result = parser.parse("2d6+1")
        pdf    = DicePdf.DicePdf()
        p      = pdf.make_base_probs(result)
        self.assertFalse(1  in p.keys())
        self.assertFalse(13 in p.keys())
        for x in range(2,13) :
            t = round(p[x], 5)
            c = round((1.0 * (6-abs(7-x)))/36.0, 5)
            self.assertEqual(t, c)
        
if __name__ == '__main__':
    unittest.main()
