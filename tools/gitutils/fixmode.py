#!/usr/bin/env python3

"""Git Checkout files that only have their mode spuriously changed."""

import os
import re
import subprocess
import sys

import upfinder

def find_git_root() :
    """Find the directory which is the root of the current git tree."""

    return bytes(upfinder.find_up('.git'), 'ascii')

def get_output_for_cmd(cmd, paths=[]) :
    """Run a command and return output."""

    temp = cmd[:]
    temp.extend(paths)
    proc = subprocess.Popen(temp, stdout=subprocess.PIPE)
    out, err = proc.communicate()
    return out

def update(paths) :
    """Perform a git checkout to fix the bad mode."""

    out = get_output_for_cmd(['git', 'checkout'], paths)


def filter_for_mode_changes(paths) :
    """Check if the only diff in a file is the mode."""

    pattern = b'^diff\\s+--git\\s+a.*\\s+b/(.*)\nold mode \\d+\nnew mode \\d+$'
    out     = get_output_for_cmd(['git', 'diff'], paths)
    mpaths  = [m.group(1) for m in re.finditer(pattern, out, re.MULTILINE)]

    paths[:] = mpaths

def main() :
    """Find all files that have spurious mode changes & fix them."""

    pattern = b'.*modified:\\s+(.*)'
    out     = get_output_for_cmd(['git', 'status'])

    paths   = [m.group(1) for m in re.finditer(pattern, out, re.MULTILINE)]

    try :
        root    = find_git_root()
    except Exception as e :
        print(e)
        sys.exit(1)

    filter_for_mode_changes(paths)
    sep = bytes(os.sep, 'ascii')
    update([root + sep + p for p in paths])

if __name__ == '__main__' :
    main()

