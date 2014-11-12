#!/usr/bin/python3

import re

class Scanner(object) :
    FIRST_LINE = 1
    CONTINUATION_LINE = 2
    UNKNOWN_LINE = 3

    def __init__(self, data) :
        self.data = data
        self.first_line_re = re.compile('([^:]+):([0-9]+):(.*)')
        self.continuation_line_re = re.compile('([^-]+)-([0-9]+)-(.*)')
    
    def group(self) :

        groupings = []
        current = []
        last_key = ''

        for line in self.data :
            line_type, line_data = self.classify_line(line)
            if line_type == Scanner.CONTINUATION_LINE :
                current.append(line_data)
            else :
                groupings.append(current)
                current = []

            if line_type != Scanner.UNKNOWN_LINE :
                current.append(line_data)
                
        groupings.append(current)
        return groupings

    def classify_line(self, line) :
        l = line[:-1]
        m = self.first_line_re.match(l)
        if m :
            return (Scanner.FIRST_LINE, m.group(1,2,3))

        m = self.continuation_line_re.match(l)
        if m :
            return (Scanner.CONTINUATION_LINE, m.group(1,2,3))

        return (Scanner.UNKNOWN_LINE, ('', '', l))

