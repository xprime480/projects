#!/usr/bin/python

def insert(item, tree) :
    test = item.split("/", 1)

    if not tree.has_key(test[0]) :
        tree[test[0]] = {}

    if len(test) > 1 :
        insert(test[1], tree[test[0]])

def display(dst, tree, prefixes) :
    for key , subtree in tree.iteritems() :
        spaces = ' ' * (4 * len(prefixes))
        dst.write('%s/%s\n' % (spaces, key))
        if subtree :
            prefixes.append(key)
            display(dst, subtree, prefixes)
            prefixes.pop()

def process(src, dst) :
    inputs = [l[:-1] for l in src.readlines()]
    inputs.sort()

    outputs = {}
    
    for i in inputs :
        insert(i, outputs)

    display(dst, outputs, [])

if __name__ == '__main__' :
    import sys
    process(sys.stdin, sys.stdout)
