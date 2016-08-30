#!/usr/bin/env python

import re
import sys

################################################################
#
def args() :
    """Parse and return the command line parameters."""

    import argparse
    import sys

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--regexp",
        help="regular expression to match blocks", 
        default='.'
    )
    parser.add_argument(
        "--separator",
        help="regexp to separate blocks", 
        default='^\+-----'
    )
    parser.add_argument(
        "--prolog",
        help="Print text before first block", 
        default=False,
        action='store_true'
    )
    parser.add_argument(
        "--epilog",
        help="Print text after last block", 
        default=False,
        action='store_true'
    )
    parser.add_argument(
        "files",
        help="Files to scan", 
        default=[],
        nargs="*"
    )

    try :
        return parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

################################################################
#
class BlockGrepper(object) :
    def __init__(self, config) :
        self.config = config
        self.matcher = re.compile(config.regexp)
        self.sep     = re.compile(config.separator)

    def run(self, file) :
        block_count = 1
        match_count = 0
        current = ''
        write_current = self.config.prolog
        last_sep = ''

        for line in file.readlines() :
            if self.sep.search(line[:-1]) :
                last_sep = line
                if write_current :
                    if match_count or not self.config.prolog :
                        print(last_sep)
                    print current
                    match_count = match_count + 1
                write_current = False
                current = ''
                block_count = block_count + 1
            else :
                current = current + line
                if self.matcher.search(line) :
                    write_current = True

        if write_current or ( self.config.epilog and current ) :
            if match_count :
                print(last_sep)
            print(current)
            match_count = match_count + 1

        return (match_count,block_count)

################################################################
#
def main() :
    cfg = args()
    bg = BlockGrepper(cfg)
    if len(cfg.files) == 0 :
        bg.run(sys.stdin)
    else :
        for file in cfg.files :
            try :
                with open(file) as fh :
                    r = bg.run(fh)
                    print('%d matches of %d blocks' % r)
            except IOError, e :
                print file, e


if __name__ == '__main__' :
    main()

