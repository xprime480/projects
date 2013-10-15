#!/usr/bin/env python3

import argparse
import os
import sys

class Decommenter(object) :
    
    def __init__(self, files, dir) :
        self.files = files
        self.dir   = dir

    def run(self) :
        """Decomment any files explicitly given, plus c++ files in dir."""
        for f in self.files :
            self.decomment_file(f)

        self.decomment_dir(self.dir)

    def decomment_file(self, f) :
        """Decomment a file."""

        if not os.access(f, os.F_OK) :
            print ('file does not exist: ', f)
            return

        if not os.access(f, os.W_OK) :
            print ('cannot overwrite file:', f)
            return

        with open(f) as fh :
            text = fh.read()

        self.make_backup(f)

        with open(f, 'w') as fh :
            size = len(text)
            i = 0
            while i < size :
                c = text[i]
                if c == '\\' :
                    i += 2
                elif c == '"' or c == '\'' :
                    i = self.skip_string(i+1, size, text, c)
                elif c == '/' :
                    end, iscomment = self.start_comment(i+1, size, text)
                    if iscomment :
                        code = text[0:i]
                        text = text[end+1:]
                        fh.write(code)
                        print (code, end='')
                        i = 0
                        size = len(text)
                    else :
                        i += 1
                else :
                    i += 1

            fh.write(text)


    def skip_string(self, i, size, text, delim) :
        """Skip the rest of a string returning the end position."""

        while i < size :
            c = text[i]
            if c == '\\' :
                i += 2
            elif c == delim :
                return i+1
            else :
                i += 1

        return i

    def start_comment(self, i, size, text) :
        """Determine if text is the start of a comment or spurious '/'"""

        if i >= size :
            return i, False

        c = text[i]
        if c == '*' :
            return self.old_style_comment(i+1, size, text)
        elif c == '/' :
            return self.new_style_comment(i+1, size, text)
        else :
            return i, False

    def old_style_comment(self, i, size, text) :
        """Just entered an old style comment, find end of line."""

        while i < size :
            if (size - i) < 2 :
                return size, False
            elif text[i: -1].startswith('*/') :
                return i+1, True
            else :
                i += 1
        
        return i, False

    def new_style_comment(self, i, size, text) :
        """Just entered a new style comment, find end of line."""

        while i < size :
            c = text[i]
            if c == '\n' :
                return i-1, True
            else :
                i += 1

        return -1, True

    def make_backup(self, path) :
        """Create a backup if the backup does not already exist."""

        backup_path = path + '.bak'
        if os.access(backup_path, os.F_OK) :
            print ('backup file already exists: ', backup_path)
            return

        os.rename(path, backup_path)
                
    def decomment_dir(self, d) :
        """Walk a directory tree and decomment each matching file."""
        
        if not d :
            return
        
        for root, dirs, files in os.walk(d) :
            for f in files :
                if f.endswith('.h') or f.endswith('.cpp') :
                    path = '' + root + os.sep + f
                    self.decomment_file(path)

def main() :
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "files",
        help="name of files to decomment",
        nargs=argparse.REMAINDER
    )
    parser.add_argument(
        "--dir",
        help="name of to search for files to decomment",
        nargs='?'
    )

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        return 1

    
    dc = Decommenter(args.files, args.dir)
    dc.run()

    return 0

if __name__ == '__main__' :
    sys.exit(main())

