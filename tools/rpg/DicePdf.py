#!/usr/bin/python3

import PdfUtils
import SpecParser

class DicePdf(object) :
    def __init__(self, spec="d6") :
        parser = SpecParser.SpecParser(spec)
        parsed = parser.parse()
        self.make_probs(parsed)

    def get(self) :
        return self.probs

    def p(self, value) :
        if value in self.probs.keys() :
            return self.probs[value]
        return 0.0

    def make_probs(self, pspec) :
        base_probs = self.make_base_probs(pspec)
        offset = pspec.offset()
        self.probs = dict([(k+offset, v) for k,v in base_probs.items()])

    def make_base_probs(self, pspec) :
        count = pspec.dice_count()
        size  = pspec.dice_size()
        one_die = self.make_single_die_pdf(size)
        pdf = one_die
        for n in range(count-1) :
            pdf = self.merge_pdfs(pdf, one_die)
        return pdf

    def make_single_die_pdf(self, size) :
        return dict([(i+1, 1.0/size) for i in range(size)])

    def merge_pdfs(self, pdf1, pdf2) :
        return PdfUtils.merge(pdf1, pdf2)
