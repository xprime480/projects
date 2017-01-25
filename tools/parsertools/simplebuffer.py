
class SimpleBuffer(object) :
    def __init__(self, gen) :
        self.data = None
        self.generator = gen

    def get(self) :
        rv = self.peek()
        self.data = None
        return rv

    def peek(self) :
        if self.data is None :
            self.data = self.generator()
        return self.data
