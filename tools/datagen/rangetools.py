
import datetime

ifmt = '%Y%m%d'

def make_date(x, ifmt=ifmt) :
    return datetime.datetime.strptime(x, ifmt)

class DateRange(object) :
    def __init__(self, start, stop, step=1, fmt=ifmt) :
        self.start = make_date(start, fmt)
        self.stop  = make_date(stop,  fmt)
        self.step  = datetime.timedelta(step)
        self.fmt   = fmt

        x = self.start + self.step
        if x <= self.start :
            raise Exception(
                'Going back in time not supported for step = %s'% str(step))


    def dates(self) :
        current = self.start 
        while current <= self.stop :
            yield current   # .strftime(self.fmt)
            current = current + self.step

    def make_gen(self) :
        return self.dates


class NumericRange(object) :
    def __init__(self, start, stop, step, fmt) :
        self.start = start
        self.stop  = stop
        self.step  = step
        self.fmt   = fmt

        if self.step == 0 :
            raise Exception(
                'Range with no step not supported')

    def make_gen(self) :
        if self.step > 0 :
            def g() :
                current = self.start 
                while current <= self.stop :
                    yield self.convert(self.fmt % current)
                    current = current + self.step
        else :
            def g() :
                current = self.start 
                while current >= self.stop :
                    yield self.convert(self.fmt % current)
                    current = current - self.step

        return g

class IntRange(NumericRange) :
    def __init__(self, start, stop, step=1, fmt='%d') :
        NumericRange.__init__(self, start, stop, step, fmt or '%d')

    def convert(self, value) :
        return int(value)
            

class FloatRange(NumericRange) :
    def __init__(self, start, stop, step=1, fmt='%f') :
        NumericRange.__init__(self, start, stop, step, fmt or '%f')

    def convert(self, value) :
        return float(value)
            

