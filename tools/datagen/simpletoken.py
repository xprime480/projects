
class SimpleToken(object) :
    def __init__(self, lineno, text, token_type, value=None) :
        self.lineno     = lineno
        self.text       = text
        self.token_type = token_type
        self.value      = value
        
    def gettext(self) :
        return self.text[:]

    def __repr__(self) :
        return 'type = %s, text = \'%s\'' % (self.token_type.__class__.__name__, self.text)

####################################################################
#
class SimpleTokenType(object) :
    pass

class Keyword(SimpleTokenType) :
    pass

class Identifier(SimpleTokenType) :
    pass

class Type(SimpleTokenType) :
    pass

class IntegerType(Type) :
    pass

class FloatType(Type) :
    pass

class StringType(Type) :
    pass

# values

class Value(SimpleTokenType) :
    pass

class IntegerValue(Value) :
    pass

class FloatValue(Value) :
    pass

class StringValue(Value) :
    pass

# miscellaneous punctuation

class LParen(SimpleTokenType) :
    pass

class RParen(SimpleTokenType) :
    pass

# operators

class Operator(SimpleTokenType) :
    pass

class Add(Operator) :
    pass

class Subtract(Operator) :
    pass

class Multiply(Operator) :
    pass

class Divide(Operator) :
    pass

class Exponent(Operator) :
    pass

class Comma(Operator) :
    pass


def add_tokens(lexer) :

    # reserved words
    #
    lexer.add_token_type_simple('integer', IntegerType())
    lexer.add_token_type_simple('float',   FloatType())
    lexer.add_token_type_simple('string',  StringType())

    # single character operators and punctuation
    #
    lexer.add_token_type_simple('+', Add())
    lexer.add_token_type_simple('-', Subtract())
    lexer.add_token_type_simple('*', Multiply())
    lexer.add_token_type_simple('/', Divide())
    lexer.add_token_type_simple(',', Comma())

    lexer.add_token_type_simple('(', LParen())
    lexer.add_token_type_simple(')', RParen())

    # multichar operators
    #
    lexer.add_token_type_regexp('\*\*', Exponent())
