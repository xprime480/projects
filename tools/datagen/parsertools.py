
from simpletoken import* 

class Result(object) :
    pass

class Success(Result) :
    def __init__(self, text, ast) :
        self.text = text
        self.ast  = ast

    def __repr__(self) :
        return str(self.ast)

class Failure(Result) :
    def __init__(self, message, lineno=0, cascade=None) :
        self.message = message
        self.lineno  = lineno
        self.cascade = cascade

    def __repr__(self) :
        if self.lineno > 0 :
            args = (self.message, self.lineno)
            text = 'parse failure: \'%s\' at line %d' % args
        else :
            text = 'parse failure: \'%s\'' % self.message

        if self.cascade :
            text += '\n --> ' + str(self.cascade)

        return text

        

##################################################################
#
class Parser(object) :
    ##################################################################
    #
    def __init__(self, tokenbuffer) :
        self.tokenbuffer = tokenbuffer

    ##################################################################
    #
    def peek(self) :
        if self.tokenbuffer :
            return self.tokenbuffer.peek()
        return None

    ##################################################################
    #
    def get(self) :
        if self.tokenbuffer :
            return self.tokenbuffer.get()
        return None

    ##################################################################
    #
    def parse_empty(self) :
        return Success('', ('NULL',))

    ##################################################################
    #
    def parse_eof(self) :
        token = self.peek()
        if token :
            return Failure('Expecting EOF, got %s' % str(token), token.lineno)

        return Success('', ('EOF',))

    ##################################################################
    #
    def parse_string_value(self, testvalue=None) :
        token = self.peek()
        if not token :
            return Failure('Expecting string value, got EOF')

        if not isinstance(token.token_type, StringValue) :
            return Failure(
                'Expecting string value, got %s' % str(token), 
                token.lineno
            )

        text  = token.gettext()
        value = text[1:-1]

        if testvalue and testvalue != value :
            args = (testvalue, value)
            return Failure(
                'Expecting string constant value \'%s\', got \'%s\'' % args, 
                token.lineno
            )                    

        self.get()
        return Success(text, ('STRING_CONST', value))


    ##################################################################
    #
    def parse_integer_value(self, testvalue=None) :
        token = self.peek()
        if not token :
            return Failure('Expecting integer value, got EOF')

        if not isinstance(token.token_type, IntegerValue) :
            return Failure(
                'Expecting integer value, got %s' % str(token), 
                token.lineno
            )

        text  = token.gettext()
        value = int(text)

        if testvalue and testvalue != value :
            args = (testvalue, value)
            return Failure(
                'Expecting integer constant value \'%d\', got \'%d\'' % args, 
                token.lineno
            )                    

        self.get()
        return Success(text, ('INTEGER_CONST', value))

                      
    ##################################################################
    #
    def parse_float_value(self, testvalue=None) :
        token = self.peek()
        if not token :
            return Failure('Expecting floating point value, got EOF')

        ttype  = token.token_type
        lineno = token.lineno
        if not isinstance(ttype, FloatValue) :
            msg = 'Expecting floating point value, got %s' % str(token)
            return Failure(msg, lineno)

        text  = token.gettext()
        value = float(text)

        if testvalue and testvalue != value :
            args = (testvalue, value)
            msg = 'Expecting floating point constant value \'%d\', got \'%d\'' % args
            return Failure(msg, lineno)                    

        self.get()
        return Success(text, ('FLOAT_CONST', value))

    ##################################################################
    #
    def parse_primitive(self) :
        """Parse one of the primitive types"""
        return self.parse_one_of(
            self.parse_string_value,
            self.parse_integer_value,
            self.parse_float_value
        )

    ##################################################################
    #
    def parse_keyword(self, testvalue=None) :
        token = self.peek()
        if not token :
            return Failure('Expecting keyword, got EOF')

        ttype  = token.token_type
        lineno = token.lineno
        if not isinstance(ttype, Keyword) :
            msg = 'Expecting keyword, got %s' % str(token)
            return Failure(msg, lineno)

        text  = token.gettext()
        value = text

        if testvalue and testvalue != value :
            msg = 'Expecting keyword \'%s\', got \'%s\'' % (testvalue, value)
            return Failure(msg, lineno)                    

        self.get()
        return Success(text, ('KEYWORD', value))

    ##################################################################
    #
    def parse_identifier(self, testvalue=None) :
        token = self.peek()
        if not token :
            return Failure('Expecting keyword, got EOF')

        ttype  = token.token_type
        lineno = token.lineno
        if not isinstance(ttype, Identifier) :
            msg = 'Expecting identifier, got %s' % str(token)
            return Failure(msg, lineno)

        text  = token.gettext()
        value = text

        if testvalue and testvalue != value :
            args = (testvalue, value)
            msg = 'Expecting identifier \'%s\', got \'%s\'' % args
            return Failure(msg, lineno)                    

        self.get()
        return Success(text, ('IDENTIFIER', value))

    ##################################################################
    #
    def parse_sequence(self, *parsers) :
        count = 0
        ast   = []
        text  = ''

        for p in parsers :
            result = p()
            if isinstance(result, Success) :
                if count > 0 :
                    text += ' '
                text += result.text
                ast.append(result.ast)
                count += 1
            elif isinstance(result, Failure) :
                msg = 'parse_sequence: failure on subparser after \'%s\''
                return Failure(msg % text, cascade = result)
            else :
                msg = 'parse_sequence: wrong type returned from subparser: \'%s\''
                return Failure(msg % result)
        
        ast.insert(0, count)
        ast.insert(0, 'SEQUENCE') 

        rv = Success(text, tuple(ast))
        return rv

    ##################################################################
    #
    def parse_list(self, item, separator) :
        count = 0
        ast   = []
        text  = ''

        first = item()
        if isinstance(first, Failure) :
            return Success('', ('LIST', 0))

        text = first.text[:]
        ast.append(first.ast)
        count = 1

        while True :
            sep = separator()
            if isinstance(sep, Failure) :
                break  # end of list, no separator seen

            it = item()
            if isinstance(it, Failure) :
                msg = 'parse_list: List terminated with separator'
                return Failure(msg, cascade=it)

            count += 1
            text += ' ' + sep.text + ' ' + it.text
            ast.extend([sep.ast, it.ast]) 

        ast.insert(0, count)
        ast.insert(0, 'LIST') 

        rv = Success(text, tuple(ast))
        return rv

    ##################################################################
    #
    def parse_repeated(self, parser, min_count=1, max_count=None) :
        if min_count == max_count == 0 :
            return self.parse_empty()
            
        count = 0
        ast   = []
        text  = ''
        msg   = None

        while True :
            if max_count and count >= max_count :
                break

            result = parser()
            if isinstance(result, Success) :
                if count > 0 :
                    text += ' '
                text += result.text
                ast.append(result.ast)
                count += 1
            elif isinstance(result, Failure) :
                msg = 'parse_repeated: failure on subparser after %d iterations' % count
                break
            else :
                msg = 'parse_repeated: wrong type returned from subparser: \'%s\'' % result
                break
                

        if count < min_count :
            if msg :
                return Failure(msg, cascade=result)

            msg = 'parse_repeated: Insufficient repetitions in input %d found, minimum %d expected'
            return Failure(msg % (count, min_count) , cascade=result)

        if count == min_count == 0 :
            return self.parse_empty()

        ast.insert(0, count)
        ast.insert(0, 'SEQUENCE') 
        return Success(text, tuple(ast))

    ##################################################################
    #
    def parse_one_of(self, *parsers) :
        if not parsers :
            return Failure('parse_one_of: no alternatives given')

        cascades = []

        for p in parsers :
            result = p()
            if isinstance(result, Success) :
                return result

            cascades.append(result)

        token = self.peek()
        if not token :
            return Failure(
                'parse_one_of: none of the alternatives matched at EOF'
            )
        
        msg = 'parse_one_of: none of the alternatives matched, looking at %s'
        return Failure(msg % str(token), token.lineno)

    ##################################################################
    #
    def parse_by_category(self, categories) :
        token = self.peek()
        if not token :
            return Failure('parse_by_category: Expecting token, got EOF')
            
        ttype = token.token_type
        text = token.gettext()[:]
        for cat in categories :
            if isinstance(ttype, cat) :
                self.get()
                ast = ('OPERATOR', text[:])
                return Success(text, ast)

        txt = 'parse_by_category: token \'%s\' not in target category/ies %s'
        return Failure(txt % (str(token), str(categories)),  token.lineno)
