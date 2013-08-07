
from simpletoken import *


class TestTokens(object) :
    def __init__(self) :
        self.int_value    = SimpleToken(1, "123",      IntegerValue(), 123)
        self.float_value  = SimpleToken(1, "0.25",     FloatValue(),   0.25)
        self.string_value = SimpleToken(1, "\'loop\'",  StringValue(),  "loop")

        self.int_type    = SimpleToken(1, "integer", IntegerType())
        self.float_type  = SimpleToken(1, "float",   FloatType())
        self.string_type = SimpleToken(1, "string",  StringType())

        self.keyword = SimpleToken(1, "loop",  Keyword())

        self.identifier = SimpleToken(1, "Mike",  Identifier())

        self.lparen = SimpleToken(1, "(", LParen())
        self.rparen = SimpleToken(1, ")", RParen())
        self.comma  = SimpleToken(1, ",", Comma())

        self.add      = SimpleToken(1, "+", Add())
        self.subtract = SimpleToken(1, "-", Subtract())
        self.multiply = SimpleToken(1, "*", Multiply())
        self.divide   = SimpleToken(1, "/", Divide())
        self.exponent = SimpleToken(1, "**", Exponent())

    def as_text(self, tokens) :
        rv = ''
        for token in tokens :
            if rv :
                rv += ' '
            rv += token.text
        return rv

    def as_values(self, tokens) :
        return [x.value for x in tokens]
