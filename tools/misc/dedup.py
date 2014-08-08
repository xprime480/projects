#!/usr/bin/python

class Deduper(object) :
    def __init__(self) :
        self.lines = {}
        self.count = 0

    def addLine(self, line) :
        self.count += 1
        self.lines[line] = self.count

    def getLines(self) :
        lineListWithIndex = [(index,line) for line,index in self.lines.items()]
        lineListWithIndex.sort()
        linesSortedByIndex = [line for index,line in lineListWithIndex]
        return linesSortedByIndex

class FileDeduper(object) :
    def __init__(fileName) :
        deduper = Deduper()
        with open(fileName) as fileHandle :
            for line in fileHandle.readlines() :
                deduper.addLine(line[:-1])
        self.lines = deduper.getLines()
    
    def getLines(self) :
        return self.lines

def dedupFile(fileName) :
    deduper = FileDeduper(fileName)
    for line in deduper.getLines :
        print line

if __name__ == '__main__' :
    import sys
    for fileName in sys.argv[1:] :
        dedupFile(fileName)
