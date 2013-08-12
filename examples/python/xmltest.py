#!/usr/bin/env python

import sys
from xml.sax import saxutils

class Name(object):
    def __init__(self, forename, surname):
        self.forename = forename
        self.surname = surname

names = [Name("Andrew", "Dalke"),
         Name("John", "Smith"),
         Name(u"\N{LATIN CAPITAL LETTER A WITH RING ABOVE}sa", "Svensson"),]

gen = saxutils.XMLGenerator(sys.stdout, "utf-8")
gen.startDocument()
gen.startElement("NameList", {})
gen.characters("\n")
for name in names:
    gen.characters("  ");
    gen.startElement("Name",
                     {"forename": name.forename,
                      "surname": name.surname})
    gen.endElement("Name")
    gen.characters("\n");
gen.endElement("NameList")
gen.characters("\n");
gen.endDocument()
