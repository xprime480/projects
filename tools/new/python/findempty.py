#!/usr/bin/python

import os
import sys

class FindEmpty(object) :
    def __init__(self, dir, target, hdr_append, data_append) :
        self.header_append = hdr_append
        self.data_append = data_append
        self.dir = dir
        self.target = target

    def make_bak(self, path) :
        bak = path[:] + '~'
        os.rename(path, bak)
        return bak

    def get_data(self, path) :
        with open(path, 'r') as f :
            text = f.readlines()
        return text

    def write_header(self, f, text) :
        if text :
            f.write(text[0][:-1])
            f.write(self.header_append)
            f.write('\n')

    def write_data(self, f, text) :
        for line in text[1:] :
            f.write(line[:-1])
            f.write(self.data_append)
            f.write('\n')

    def write_modified(self, text, path) :
        with open(path, 'w') as f :
            self.write_header(f, text)
            self.write_data(f, text)

    def fixup(self, path) :
        bak = self.make_bak(path)
        text = self.get_data(bak)
        self.write_modified(text, path)

    def walk(self) :
        for root, dirs, files in os.walk(dir) :
            if self.target in files :
                self.fixup(os.path.join(root, self.target))

if __name__ == '__main__' :
    for f in sys.argv[1:] :
        w = find_non_prefix(f)
