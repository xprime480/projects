#!/usr/bin/python

import sys
import mimetools

def main() :
    fname_src = sys.argv[1]
    fname_dst = sys.argv[2]

    with open(fname_src) as src :
        with open(fname_dst, 'w') as dst :
            mimetools.decode(src, dst, 'base64')

if __name__ == '__main__' :
    main()
