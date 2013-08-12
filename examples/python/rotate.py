#!/bin/env python

import string

def decode(str, rotate) :
    translator =  string.maketrans(string.lowercase,
                                   string.lowercase[rotate:] +
                                   string.lowercase[:rotate])
    return str.translate(translator)


if '__main__' == __name__ :
    coded = """g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."""


    print decode(coded, 2)
    print
    print decode('map',2)
