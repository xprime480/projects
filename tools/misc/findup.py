#!/usr/bin/env python3

"""Find a file by going up the directory tree."""

import os
import sys

class NotFoundException(Exception) :
    def __init__(self, msg) :
        super().__init__(msg)


def find_up(path) :
    """Return the first directory at or above cwd containing path."""

    curr  = os.getcwd()
    last  = curr + os.sep + 'just something extra'

    while curr != last :
        if path in os.listdir(curr) :
            return curr
        last = curr
        curr = os.path.abspath(last + os.sep + os.pardir)
        if os.name == 'posix' and last == os.sep :
            break               # This is only correct on linux/cygwin

    raise NotFoundException('Reached the root, file not found.')


def main() :
    """Find the directory containing each file."""

    for p in sys.argv[1:] :
        try :
            d = find_up(p)
            print (p, d)
        except NotFoundException :
            print (p, 'not found between current directory and root.')
        except Exception as e :
            print (p, e)

if __name__ == '__main__' :
    main()

