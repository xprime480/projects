
from simpletoken import *
import simpletoken

class DatagenToken(SimpleToken) :
    def __init__(self, lineno, text, token_type, value=None) :
        SimpleToken.__init__(self, lineno, text, token_type, value)

####################################################################
#
class ListKwd(Keyword) :
    pass

class ReadOnly(ListKwd) :
    pass

class ReadWrite(ListKwd) :
    pass

class Temporary(ListKwd) :
    pass

class Generated(ListKwd) :
    pass

class Loop(Keyword) :
    pass

class IOKwd(Keyword) :
    pass

class Input(IOKwd) :
    pass

class Output(IOKwd) :
    pass

class Colon(Operator) :
    pass

class Format(Operator) :
    pass

class As(Operator) :
    pass

class Range(Operator) :
    pass

class DateType(Type) :
    pass

class DateValue(Value) :
    pass


rokw  = 'readonly'
rwkw  = 'readwrite'
genkw = 'generated'
tmpkw = 'temporary'

inpkw = 'input'
outkw = 'output'

def add_tokens(lexer) :
    simpletoken.add_tokens(lexer)

    # reserved words
    #
    lexer.add_token_type_simple(rokw,   ReadOnly())
    lexer.add_token_type_simple(rwkw,   ReadWrite())
    lexer.add_token_type_simple(genkw,  Generated())
    lexer.add_token_type_simple(tmpkw,  Temporary())

    lexer.add_token_type_simple(inpkw,  Input())
    lexer.add_token_type_simple(outkw,  Output())

    lexer.add_token_type_simple('loop', Loop())

    lexer.add_token_type_simple('date',   DateType())
    lexer.add_token_type_simple('double', simpletoken.FloatType())
    
    # single character operators
    #
    lexer.add_token_type_simple(':',  Colon())

    # multichar operators
    #
    lexer.add_token_type_regexp('format', Format())
    lexer.add_token_type_regexp('as',     As())
    lexer.add_token_type_regexp('range',  Range())


def get_valid_categories() :
    return [rokw, rwkw, genkw, tmpkw]

def get_valid_io() :
    return [inpkw, outkw]
