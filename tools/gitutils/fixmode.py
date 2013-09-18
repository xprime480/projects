#!/usr/bin/env python3

"""Git Checkout files that only have their mode spuriously changed."""

import re
import subprocess

def check_diff(path) :
    """Check if the only diff in a file is the mode."""

    proc = subprocess.Popen(
        ['git', 'diff', path], 
        stdout=subprocess.PIPE
    )
    out,err  = proc.communicate()
    lines    = out.split(b'\n')
    if ( len(lines) == 4 and 
         lines[1].startswith(b'old mode ') and 
         lines[2].startswith(b'new mode ') ) :
        print('updating', path, 'because of wonky mode change.')
        p2 = subprocess.Popen(
            ['git', 'checkout', path], 
            stdout=subprocess.PIPE
        )
        p2.communicate()

def main() :
    """Find all files that have spurious mode changes & fix them."""

    regex = re.compile(b'.*modified:\\s+(.*)')

    proc     = subprocess.Popen(['git', 'status'], stdout=subprocess.PIPE)
    out,err  = proc.communicate()
    lines    = out.split(b'\n')
    for line in lines :
        match = regex.match(line)
        if match :
            check_diff(match.group(1))

if __name__ == '__main__' :
    main()
    
