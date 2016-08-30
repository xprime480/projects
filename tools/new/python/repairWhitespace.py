#!/usr/bin/python 

import sys, subprocess, os

def runTerminalCommand(args):
    p = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return p.communicate()

def removeTrailingWhitespace(string):
    return string.rstrip()

def convertTabsToSpaces(string):
    return string.replace("\t", '    ')

def getFileName():
    return sys.argv[1]

def modifyFile(fileName):
    f = open(fileName, 'r')

    lines = f.readlines()

    f.close()

    f = open(fileName, 'w')

    for line in lines:
        f.write(convertTabsToSpaces(removeTrailingWhitespace(line)) + '\n')

    f.close()

if len(sys.argv) > 1:
    modifyFile(getFileName())
else:
    src = os.environ['SRC']
    if len(src) == 0:
        print "$SRC environment variable not set. Exiting..."
    else:
        out, err = runTerminalCommand(["git","diff-tree","--no-commit-id","--name-only","-r", "--diff-filter=A", "HEAD"])
        if len(err) > 0:
            print "No additions in git commit:\n" + err
        else:
            for line in out.split("\n"):
                if len(line) > 0:
                    modifyFile('/'.join([src, line.strip()]))
        out, err = runTerminalCommand(["git","diff-tree","--no-commit-id","--name-only","-r", "--diff-filter=M", "HEAD"])
        if len(err) > 0:
            print "No modifications in git commit:\n" + err
        else:
            for line in out.split("\n"):
                if len(line) > 0:
                    modifyFile('/'.join([src, line.strip()]))

