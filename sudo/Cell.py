#!/usr/bin/python


class CellException(Exception) :
    def __init__(self, msg) :
        self.msg = msg


class Cell(object) :
    def __init__(self, size) :
        self.value = -1
        self.choices = set(range(1,1+size))
        self.valid = True

    def is_set(self) :
        return self.valid and self.value <> -1

    def set(self, val) :
        self.__check()
        if self.value == -1 and val in self.choices :
            self.choices = set([val])
            self.value = val
        elif val not in self.choices :
            raise CellException("Value not allowed")
        elif self.value <> val:
            raise CellException("Value locked")

    def get(self) :
        self.__check()
        return self.choices

    def get_value(self) :
        if not self.is_set() :
            raise CellException("Cell is not set")
        return self.value

    def remove(self, vals) :
        """Remove a set of VALS from the possible values for cell.

        Return True iff the possible values went to exactly one choice.
        """

        self.__check()
        if self.value <> -1 :
            raise CellException("Value locked")

        self.choices = self.choices - set(vals)

        if len(self.choices) == 0 :
            self.valid = False
            raise CellException("All possible values removed")

        if len(self.choices) == 1 :
            self.set(list(self.choices)[0])
            return True

        return False
            
    def __check(self) :
        if not self.valid :
            raise CellException("Invalid Cell")

def with_failure(a, show=True) :
    try :
        a()
        print "Should not get here"
    except CellException as e :
        if show :
            print e.msg

def test() :
    c = Cell(9)
    print c.get()
    c.remove(range(5))
    print c.get()
    done = c.remove(range(6,10))
    print c.get()
    if done :
        print "Cell now locked"
    with_failure(lambda : c.remove([]))
    print c.is_set()
    print c.get_value()

    c = Cell(9)
    print c.is_set()
    with_failure(lambda : c.get_value())
    with_failure(lambda : c.remove(range(99)))
    with_failure(lambda : c.set(3))

    c = Cell(9)
    with_failure(lambda : c.remove(range(99)), False)
    with_failure(lambda : c.get())
    
    c = Cell(9)
    c.set(3)
    print c.get()
    with_failure(lambda : c.set(3))

    c = Cell(9)
    with_failure(lambda : c.set(299))

    c = Cell(500)
    c.set(299)
    print c.get_value()

if __name__ == '__main__' :
    test()
