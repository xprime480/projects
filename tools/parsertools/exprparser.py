
from parsertools import *

##################################################################
#

class ExpressionParser(Parser) :

    ##################################################################
    #
    def __init__(self, tokenbuffer) :
        Parser.__init__(self, tokenbuffer)

    ##################################################################
    #
    def associate_left(self, ast) :
        """Join a list of left associative operators and operands"""

        #print 'associate_left input', ast

        ast = list(ast)
        while len(ast) > 1 :
            left = ast[:3]
            ast = ast[3:]
            ast.insert(0, (left[1], left[0], left[2]))

        ast = ast[0]
        #print 'associate_left output', ast
        return ast 

    ##################################################################
    #
    def associate_right(self, ast) :
        """Join a list of right associative operators and operands"""

        #print 'associate_right input', ast

        ast = list(ast)
        while len(ast) > 1 :
            right = ast[-3:]
            ast = ast[:-3]
            ast.append((right[1], right[0], right[2]))

        ast = ast[0]
        #print 'associate_right output', ast
        return ast 

    ##################################################################
    #
    def join_a_parsed_list(self, item_parser, separators, joiner) :
        def sep_parser() :
            return self.parse_by_category(separators)
            
        parse = self.parse_list(item_parser, sep_parser)
        #print 'join_a_parsed_list  got: ', parse

        if isinstance(parse, Failure) :
            return parse

        if parse.ast[1] == 0 :
            return Failure('No more expression input')

        text = parse.text
        ast  = joiner(parse.ast[2:])
        return Success(text, ast)
        

    ##################################################################
    #
    def parse_expression(self) :
        rv = self.parse_add_ops()
        return rv

    ##################################################################
    #
    def parse_add_ops(self) :
        return self.join_a_parsed_list(
            self.parse_mul_ops, 
            [Add, Subtract],
            self.associate_left
        )
        
    ##################################################################
    #
    def parse_mul_ops(self) :
        return self.join_a_parsed_list(
            self.parse_exp_ops, 
            [Multiply, Divide],
            self.associate_left
        )

    ##################################################################
    #
    def parse_exp_ops(self) :
        return self.join_a_parsed_list(
            self.parse_unary_op, 
            [Exponent],
            self.associate_right
        )

    ##################################################################
    #
    def parse_unary_op(self) :
        sign  = self.parse_by_category([Add, Subtract])
        value = self.parse_primary()

        if isinstance(sign, Failure) :
            return value

        if isinstance(value, Failure) :
            return Failure(
                'No primary expression found after sign',
                cascade = value
            )

        text = sign.text[:] + ' ' + value.text[:]
        ast  = (sign.ast, value.ast)
        return Success(text, ast)
        

    ##################################################################
    #
    def parse_primary(self) :
        return self.parse_one_of(
            self.parse_integer_value,
            self.parse_float_value,
            self.parse_string_value,
            self.parse_identifier_or_function,
            self.parse_parenthesized
        )

    ##################################################################
    #
    def parse_identifier_or_function(self) :
        identifier = self.parse_identifier()
        #print identifier
        if isinstance(identifier, Failure) :
            return identifier

        token = self.peek()
        #print token
        if not token :
            return identifier

        if not isinstance(token.token_type, LParen) :
            return identifier

        self.get()
        text = identifier.text[:] + ' ' + token.gettext()[:]
        
        def pcomma() :
            return self.parse_by_category([Comma])
        
        args = self.parse_list(self.parse_expression, pcomma)
        #print args

        if isinstance(args, Failure) :
            return Failure(
                'Unable to parse argument list after \'%s\'' % text, 
                cascade = args
            )

        if args.ast[1] > 0 :
            text += ' '
        text +=  args.text[:]

        token = self.peek()
        #print token
        if not token :
            return Failure('Expected \')\' after \'%s\'' % text)

        if not isinstance(token.token_type, RParen) :
            msg = 'Expected \')\' after \'%s\', got \'%s\''
            return Failure(msg % (text, token.gettext()))

        self.get()

        text += ' ' + token.gettext()
        args_ast = ['SEQUENCE', args.ast[1]]
        args_ast.extend(list(args.ast[2:len(args.ast):2]))
        ast = ('FUNCALL', identifier.ast, tuple(args_ast))

        return Success(text, ast)

    ##################################################################
    #
    def parse_parenthesized(self) :
        token = self.peek()
        if not token :
            return Failure('Expecting left parenthesis, got EOF')

        if not isinstance(token.token_type, LParen) :
            return Failure('Expecting left parenthesis value, got %s' % str(token), 
                           token.lineno)

        text  = token.gettext()[:]
        self.get()

        expr = self.parse_expression()
        if not isinstance(expr, Success) :
            return expr

        print (expr)

        text += ' '
        text += expr.text[:]

        token = self.peek()
        if not token :
            return Failure('Expecting right parenthesis, got EOF')

        if not isinstance(token.token_type, RParen) :
            return Failure('Expecting right parenthesis value, got %s' % str(token), 
                           token.lineno)

        text += ' '
        text += token.gettext()[:]
        self.get()

        return Success(text, expr.ast)

    ##################################################################
    #
    def parse_parenthesized(self) :
        token = self.peek()
        if not token :
            return Failure('Expecting left parenthesis, got EOF')

        if not isinstance(token.token_type, LParen) :
            return Failure('Expecting left parenthesis value, got %s' % str(token), 
                           token.lineno)

        text  = token.gettext()[:]
        self.get()

        expr = self.parse_expression()
        if not isinstance(expr, Success) :
            return expr

        text += ' '
        text += expr.text[:]

        token = self.peek()
        if not token :
            return Failure('Expecting right parenthesis, got EOF')

        if not isinstance(token.token_type, RParen) :
            return Failure('Expecting right parenthesis value, got %s' % str(token), 
                           token.lineno)

        text += ' '
        text += token.gettext()[:]
        self.get()

        return Success(text, expr.ast)

    ##################################################################
    #
    def deparse_infix(self, expr) :
        size = len(expr)
        if size == 0 :
            return ''

        op_code = expr[0]
        if op_code == 'FUNCALL' :
            fn_name = expr[1][1]
            fn_args = expr[2][2:]
            args    = ', '.join(map(self.deparse_infix, fn_args))
            return fn_name + '(' + args + ')'
        elif op_code in ['IDENTIFIER', 'INTEGER_CONST', 'FLOAT_CONST'] :
            return str(expr[1])
        elif op_code == 'STRING_CONST' :
            return '\'%s\'' % expr[1]

        op_code = op_code[0]
        if op_code == 'OPERATOR' :
            op = expr[0][1]
            if size == 1 :
                # any 0 arg infix operators?
                return op
            lhs = self.deparse_infix(expr[1])
            if size == 2 :
                # unary operator
                return '(' + op + ' ' + lhs + ')'
            rhs = self.deparse_infix(expr[2])
            if size == 3 :
                # binary operator
                return '(' + lhs + ' ' + op + ' ' + rhs + ')'
            return 'Error deparsing \'%s\'' % str(expr)
        else :
            return 'Unknown op code in expr: %s' % str(expr)
    
