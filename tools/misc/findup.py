#!/usr/bin/env python3

"""Find a file by going up the directory tree."""

import sys

import upfinder

def main() :
    """Find the directory containing each file."""

    for p in sys.argv[1:] :
        try :
            d = upfinder.find_up(p)
            print (p, d)
        except upfinder.NotFoundException :
            print (p, 'not found between current directory and root.')
        except Exception as e :
            print (p, e)

if __name__ == '__main__' :
    main()

