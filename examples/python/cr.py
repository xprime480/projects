#!/usr/bin/env python

from BeautifulSoup import *
from xutils import *
from re import compile

class Form(object) :
    def __init__(self, node) :
        #print node.prettify()
        self.node = node

    def getInputs(self) :
        if 'inputs' in dir(self) :
            return self.inputs

        self.inputs = {}

        data = self.node.fetch('input')
        for datum in data :
            print datum
            continue
            print datum['name']
            if 'id' in datum and 'value' in datum :
                self.inputs[datum['id']] = datum['value']
            else :
                print datum.prettify()

        return self.inputs

    def __repr__(self) :
        s = str(self.inputs)
        return s

class CR(object) :
    def __init__(self, stream) :
        self.soup = cookSoup(stream)

    def getComments(self) :
        if 'comments' in dir(self) :
            return self.comments
        
        prefix        = 'comment_text_'
        prefixlen     = len(prefix)
        raw           = self.soup.fetch('pre')
        self.comments = []
        for comment in raw :
            id = comment['id']
            if len(id) < prefixlen or id[:prefixlen] <> prefix :
                continue
            data = comment.fetchText(lambda x : True)
            l = ''.join(data)
            c = convertEntity(l)
            self.comments.append(c)

        return self.comments

    def getChangeForm(self) :
        if 'changeform' in dir(self) :
            return self.changeform

        data = self.soup.fetch('form', {'name':'changeform'})
        if len(data) :
            self.changeform = Form(data[0])
        else :
            self.changeform = None
        return self.changeform

    def __repr__(self) :
        s = self.soup.body.prettify()
        return s

for f in ['cr.html'] :
    cr = CR(open(f))
    for comment in cr.getComments() :
        ##print comment
        ##print '-' * 64
        pass
    print cr.getChangeForm().getInputs()
    print '*' * 64
    
