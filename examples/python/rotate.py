#!/usr/bin/env python3

import string

def decode(str, rotate) :
    lc = bytes(string.ascii_lowercase, encoding='ascii')
    translator =  bytes.maketrans(lc, lc[rotate:] + lc[:rotate])
    return str.translate(translator)


if '__main__' == __name__ :
    coded = """g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."""


    print(decode(coded, 2))
    print()
    print(decode('map',2))
