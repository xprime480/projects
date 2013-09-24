#!/usr/bin/env python3

"""Find a file by going up the directory tree."""

import os

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
