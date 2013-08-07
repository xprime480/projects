
class TestBuffer(object) :
    def __init__(self, tokens) :
        self.tokens = tokens[:]
        self.size   = len(self.tokens)
        self.index  = 0

    def get(self) :
        rv = self.peek()
        if rv :
            self.index += 1
        return rv

    def peek(self) :
        if self.index >= self.size :
            rv = None
        else :
            rv = self.tokens[self.index]

        #print 'TestBuffer returning %s' % rv
        return rv
