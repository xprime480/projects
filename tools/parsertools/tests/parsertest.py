#!/usr/bin/python

import unittest
from parsertools import *
from exprparser import *
import testbuffer
from testtokens import *

gTokens            = TestTokens()

gTokens_Empty      = []

gTokens_F          = [gTokens.float_value]
gTokens_FT         = [gTokens.float_type]
gTokens_I          = [gTokens.int_value]
gTokens_IT         = [gTokens.int_type]
gTokens_S          = [gTokens.string_value]
gTokens_ST         = [gTokens.string_type]

gTokens_KW         = [gTokens.keyword]
gTokens_ID         = [gTokens.identifier]

gTokens_F_I        = [gTokens.float_value, gTokens.int_value]
gTokens_I_2        = [gTokens.int_value, gTokens.int_value] 
gTokens_I_3        = [gTokens.int_value, gTokens.int_value, gTokens.int_value]
gTokens_I_4        = [gTokens.int_value, gTokens.int_value, gTokens.int_value,
                      gTokens.int_value]

##################################################################
##################################################################
#
class ParserTester(unittest.TestCase) :

    ##################################################################
    #
    def __init__(self, n='runTest', basic_tokens=[]) :
        unittest.TestCase.__init__(self, n)
        self.basic_tokens = basic_tokens[:]
        self.text         = gTokens.as_text(self.basic_tokens)
        self.values       = gTokens.as_values(self.basic_tokens)

    ##################################################################
    #
    def init_parser(self, contents=[]) :
        buf    = testbuffer.TestBuffer(contents)
        parser = Parser(buf)
        return parser

    ##################################################################
    #
    def just_print(self, a) :
        print (a)

    ##################################################################
    #
    def just_pass(self, a) :
        pass

    ##################################################################
    #
    def run_test_success(self, tokens, executor, text, ast_check) :
        if tokens :
            parser = self.init_parser(tokens)
        else :
            parser = self.init_parser()

        result = executor(parser)

        if isinstance(result, Failure) :
            print (result)

        self.assertTrue(isinstance(result, Success))
        self.assertEqual(text, result.text)
        ast_check(result.ast)

    ##################################################################
    #
    def run_test_failure(self, tokens, executor) :
        if tokens :
            parser = self.init_parser(tokens)
        else :
            parser = self.init_parser()

        result = executor(parser)
        self.assertTrue(isinstance(result, Failure))

    ##################################################################
    #
    def assertAstNull(self, ast) :
        self.assertEqual(1, len(ast))
        self.assertEqual('NULL', ast[0])

    ##################################################################
    #
    def assertTypeValue(self, ast, type_tag, value) :
        self.assertEqual(2, len(ast))
        self.assertEqual(type_tag, ast[0])
        if value :
            if type(value) == type([]) :
                self.assertTrue(ast[1] in value)
            else :
                self.assertEqual(value, ast[1])

    ##################################################################
    #
    def assertAstSigned(self, ast, value, value_verifier) :
        self.assertEqual(2, len(ast))
        self.assertAstOperator(ast[0], ['+', '-'])
        value_verifier(ast[1], value)

    ##################################################################
    #
    def assertAstString(self, ast, value) :
        self.assertTypeValue(ast, 'STRING_CONST', value)

    ##################################################################
    #
    def assertAstInteger(self, ast, value) :
        self.assertTypeValue(ast, 'INTEGER_CONST', value)

    ##################################################################
    #
    def assertAstFloat(self, ast, value) :
        self.assertTypeValue(ast, 'FLOAT_CONST', value)

    ##################################################################
    #
    def assertAstKeyword(self, ast, value) :
        self.assertTypeValue(ast, 'KEYWORD', value)

    ##################################################################
    #
    def assertAstIdentifier(self, ast, value) :
        self.assertTypeValue(ast, 'IDENTIFIER', value)

    ##################################################################
    #
    def assertAstOperator(self, ast, value) :
        self.assertTypeValue(ast, 'OPERATOR', value)

    ##################################################################
    #
    def assertAstSequence(self, ast, verifiers=[]) :
        size = len(verifiers)
        self.assertEqual(2 + size, len(ast))
        self.assertEqual('SEQUENCE', ast[0])
        self.assertEqual(size,       ast[1])
        for idx in range(size) :
            verifiers[idx](ast[idx+2])

    ##################################################################
    #
    def assertAstList(self, ast, count, verifiers=[]) :
        size = len(ast)
        self.assertTrue(size >= 2)
        self.assertEqual('LIST', ast[0])
        count = ast[1]
        if count == 0 :
            self.assertEqual(size, 2)
        else :
            self.assertEqual(size, 2 + 2*count-1)

        for idx in range(len(verifiers)) :
            verifiers[idx](ast[2*idx+2])

    ##################################################################
    #
    def assertAstFuncall(self, ast, name=None, verifiers=[]) :
        self.assertEqual(3, len(ast))
        self.assertEqual('FUNCALL', ast[0])
        self.assertAstIdentifier(ast[1], name)

        arglist = ast[2]
        v = verifiers[:]
        while len(v) < arglist[1] :
            v.append(self.just_pass)
        self.assertAstSequence(arglist, v)
            
##################################################################
##################################################################
#
class EmptyParserTester(ParserTester) :
    """test the parse_parse_empty method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ParserTester.__init__(self, n, [])

    ##################################################################
    #
    def exec_basic(self, p) :
        return p.parse_empty()

    ##################################################################
    #
    def test_successes(self) :
        """parse nothing"""
        self.run_test_success(None, self.exec_basic, '', self.assertAstNull)


##################################################################
##################################################################
#
class ValueTypesParserTester(ParserTester) :
    """test various methods that return atomic values"""

    ##################################################################
    #
    def __init__(self, n='runTest', good_input=[]) :
        ParserTester.__init__(self, n, good_input)
        
        self.bad_inputs = []

    ##################################################################
    #
    def test_failures_any(self) :
        """Parse a value from inputs which do not yield values of right type"""
        for ti in self.bad_inputs :
            self.run_test_failure(ti, self.fns['eb'])

    ##################################################################
    #
    def test_failures_specific(self) :
        """Parse a value from various inputs that do not specific value"""
        for ti in self.bad_inputs :
            self.run_test_failure(ti, self.fns['ess'])

    ##################################################################
    #
    def test_failure_wrong_value(self) :
        """Parse a string from a string with the wrong expected value"""
        if self.text :
            self.run_test_failure(self.basic_tokens, self.fns['esf'])

    ##################################################################
    #
    def test_success_basic(self) :
        """Parse a string value from correct input"""
        if self.text :
            self.run_test_failure(self.basic_tokens, self.fns['esf'])
            self.run_test_success(self.basic_tokens, 
                                  self.fns['eb'], 
                                  self.text, 
                                  self.fns['ast'])

    ##################################################################
    #
    def test_success_specific(self) :
        """Parse a string constant from correct input"""
        if self.text :
            self.run_test_failure(self.basic_tokens, self.fns['esf'])
            self.run_test_success(self.basic_tokens, 
                                  self.fns['ess'], 
                                  self.text, 
                                  self.fns['ast'])

##################################################################
##################################################################
#
class StringValueParserTester(ValueTypesParserTester) :
    """test the parse_string_value method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ValueTypesParserTester.__init__(self, n, gTokens_S)

        self.bad_inputs = [None, gTokens_I, gTokens_F, gTokens_ST]

        def eb(p) :
            """parses for a string with no value restriction"""
            return p.parse_string_value()

        def esf(p) :
            """parses for a string with a particular value"""
            s = self.values[0][:] + 'something extra'
            return p.parse_string_value(s)

        def ess(p) :
            """parses for a string with a particular value"""
            s = self.values[0]
            return p.parse_string_value(s)

        def ast(a) :
            """Verifies the AST of successful parses"""
            self.assertAstString(a, self.values[0])

        self.fns = {
            'eb'  : eb,
            'esf' : esf,
            'ess' : ess,
            'ast' : ast
        }

##################################################################
##################################################################
#
class IntegerValueParserTester(ValueTypesParserTester) :
    """test the parse_integer_value method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ValueTypesParserTester.__init__(self, n, gTokens_I)

        self.bad_inputs = [None, gTokens_S, gTokens_F, gTokens_ST]

        def eb(p) :
            """parses for an integer with no value restriction"""
            return p.parse_integer_value()

        def esf(p) :
            """parses for an integer with a particular value"""
            s = self.values[0] + 1
            return p.parse_integer_value(s)

        def ess(p) :
            """parses for an integer with a particular value"""
            s = self.values[0]
            return p.parse_integer_value(s)

        def ast(a) :
            """Verifies the AST of successful parses"""
            self.assertAstInteger(a, self.values[0])

        self.fns = {
            'eb'  : eb,
            'esf' : esf,
            'ess' : ess,
            'ast' : ast
        }

##################################################################
##################################################################
#
class FloatValueParserTester(ValueTypesParserTester) :
    """test the parse_float_value method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ValueTypesParserTester.__init__(self, n, gTokens_F)

        self.bad_inputs = [None, gTokens_S, gTokens_I, gTokens_ST]

        def eb(p) :
            """parses for a float with no value restriction"""
            return p.parse_float_value()

        def esf(p) :
            """parses for a float with a particular value"""
            s = self.values[0] + 1.0
            return p.parse_float_value(s)

        def ess(p) :
            """parses for a float with a particular value"""
            s = self.values[0]
            return p.parse_float_value(s)

        def ast(a) :
            """Verifies the AST of successful parses"""
            self.assertAstFloat(a, self.values[0])

        self.fns = {
            'eb'  : eb,
            'esf' : esf,
            'ess' : ess,
            'ast' : ast
        }

##################################################################
##################################################################
#
class KeywordParserTester(ValueTypesParserTester) :
    """test the parse_keyword method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ValueTypesParserTester.__init__(self, n, gTokens_KW)

        self.bad_inputs = [None, gTokens_S, gTokens_I, gTokens_F, gTokens_ST]

        def eb(p) :
            """parses for a keyword with no value restriction"""
            return p.parse_keyword()

        def esf(p) :
            """parses for a keyword with a particular value"""
            s = self.text[:] + 'xxx' # for now keyword tokens have no value
            return p.parse_keyword(s)

        def ess(p) :
            """parses for a keyword with a particular value"""
            s = self.text[:]
            return p.parse_keyword(s)

        def ast(a) :
            """Verifies the AST of successful parses"""
            self.assertAstKeyword(a, self.values[0])

        self.fns = {
            'eb'  : eb,
            'esf' : esf,
            'ess' : ess,
            'ast' : ast
        }

##################################################################
##################################################################
#
class IdentifierParserTester(ValueTypesParserTester) :
    """test the parse_identifier method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ValueTypesParserTester.__init__(self, n, gTokens_ID)

        self.bad_inputs = [None, gTokens_S, gTokens_I, gTokens_F, gTokens_ST]

        def eb(p) :
            """parses for a identifier with no value restriction"""
            return p.parse_identifier()

        def esf(p) :
            """parses for a identifier with a particular value"""
            s = self.text[:] + 'xxx' # for now identifier tokens have no value
            return p.parse_identifier(s)

        def ess(p) :
            """parses for a identifier with a particular value"""
            s = self.text[:]
            return p.parse_identifier(s)

        def ast(a) :
            """Verifies the AST of successful parses"""
            self.assertAstIdentifier(a, self.values[0])

        self.fns = {
            'eb'  : eb,
            'esf' : esf,
            'ess' : ess,
            'ast' : ast
        }


##################################################################
##################################################################
#
class SequenceTypeParserTester(ParserTester) :

    ##################################################################
    #
    def __init__(self, n='runTest') :
        ParserTester.__init__(self, n, [])

    ##################################################################
    #
    def make_float_verifier(self, value) :
        def foo(ast) :
            self.assertAstFloat(ast, value)
        return foo

    ##################################################################
    #
    def make_int_verifier(self, value) :
        def foo(ast) :
            self.assertAstInteger(ast, value)
        return foo

    ##################################################################
    #
    def execute_test_case_failure(self, inputs, subparser) :
        """Execute test case by running the subparser on each input to get failure"""
            
        for ti in inputs :
            self.run_test_failure(ti, subparser)

    ##################################################################
    #
    def execute_test_case_success(self, inputs, outputs, subparser) :
        """Execute test case by running the subparser on each input to get expected output"""
        def make_verifiers() :
            verifiers = []
            for t in outputs :
                token_type = t.token_type
                value = gTokens.as_values([t])[0]
                if isinstance(token_type, FloatValue) :
                    verifiers.append(self.make_float_verifier(value))
                elif isinstance(token_type, IntegerValue) :
                    verifiers.append(self.make_int_verifier(value))
                else :
                    def foo(ast) :
                        print ('unable to verify', ast)
                        self.assertTrue(False)
                    verifiers.append(foo)

            return verifiers

        text = gTokens.as_text(outputs)
            
        for ti in inputs :
            self.run_test_success(
                ti, 
                subparser, 
                text, 
                lambda a : self.assertAstSequence(a, make_verifiers())
            )



##################################################################
##################################################################
#
class SequenceParserTester(SequenceTypeParserTester) :
    """test the parse_sequence method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        SequenceTypeParserTester.__init__(self, n)

    ##################################################################
    #
    def test_parse_empty_sequence(self) :
        """parse an empty sequence out of various input"""

        def plocal(p) :
            return p.parse_sequence()

        self.execute_test_case_success([None, gTokens_F], [], plocal)

    ##################################################################
    #
    def test_parse_float_sequence(self) :
        """parse a length one sequence with valid input"""

        def plocal(p) :
            return p.parse_sequence(p.parse_float_value)

        self.execute_test_case_success([gTokens_F], gTokens_F, plocal)

    ##################################################################
    #
    def test_parse_float_int_sequence(self) :
        """parse a length two sequence with valid heterogenous input"""

        def plocal(p) :
            return p.parse_sequence(
                p.parse_float_value,
                p.parse_integer_value
            )

        self.execute_test_case_success([gTokens_F_I], gTokens_F_I, plocal)

    ##################################################################
    #
    def test_parse_int_int_sequence(self) :
        """parse a length two sequence with valid homogenous input"""

        def plocal(p) :
            return p.parse_sequence(
                p.parse_integer_value, 
                p.parse_integer_value
            )

        self.execute_test_case_success([gTokens_I_2], gTokens_I_2, plocal)

    ##################################################################
    #
    def test_parse_short_input(self) :
        """parse a sequence with insufficient input"""

        def plocal(p) :
            return p.parse_sequence(
                p.parse_integer_value,
                p.parse_integer_value,
                p.parse_integer_value
            )

        self.execute_test_case_failure([gTokens_I_2], plocal)

    ##################################################################
    #
    def test_parse_wrong_sequence(self) :
        """parse a sequence with wrong type input"""

        def plocal(p) :
            return p.parse_sequence(
                p.parse_integer_value,
                p.parse_string_value
            )

        self.execute_test_case_failure([gTokens_I, gTokens_I_2], plocal)

    ##################################################################
    #
    def test_parse_subsequence(self) :
        """parse a length two sequence with a subsequence"""

        def plocal(p) :
            fpi = p.parse_integer_value
            def ftemp() :
                return p.parse_sequence(fpi, fpi)
            return p.parse_sequence(fpi, ftemp)

        values = gTokens.as_values(gTokens_I_3)

        def subv(a) :
            v = [self.make_int_verifier(values[1]), 
                 self.make_int_verifier(values[2])]
            self.assertAstSequence(a, v)

        def topv(a) :
            v = [self.make_int_verifier(values[0]), subv]
            self.assertAstSequence(a, v)

        self.run_test_success(
            gTokens_I_3, 
            plocal, 
            gTokens.as_text(gTokens_I_3), 
            topv
        )

##################################################################
##################################################################
#
class ListParserTester(SequenceTypeParserTester) :
    """test the parse_list method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        SequenceTypeParserTester.__init__(self, n)

    def plocal(self, p) :
        def sep() :
            return p.parse_by_category([Comma])
        def item() :
            return p.parse_integer_value()

        return p.parse_list(item, sep)

    ##################################################################
    #
    def test_empty_list(self) :
        """test that an empty list is accepted"""

        self.run_test_success([], 
                              self.plocal,
                              gTokens.as_text([]),
                              lambda a : self.assertAstList(a, 0)
        )

    ##################################################################
    #
    def test_singleton_list(self) :
        """test that a singleton list is accepted"""

        tokens = [gTokens.int_value]

        self.run_test_success(tokens, 
                              self.plocal,
                              gTokens.as_text(tokens),
                              lambda a : self.assertAstList(a, 1)
        )

    ##################################################################
    #
    def test_list_of_3(self) :
        """test that a list with three values is accepted"""

        tokens = [
            gTokens.int_value,
            gTokens.comma,
            gTokens.int_value,
            gTokens.comma,
            gTokens.int_value
        ]

        self.run_test_success(tokens, 
                              self.plocal,
                              gTokens.as_text(tokens),
                              lambda a : self.assertAstList(a, 3)
        )
    
    ##################################################################
    #
    def test_list_with_trailing_separator (self) :
        """test that a list with trailing separator is rejected"""

        tokens = [
            gTokens.int_value,
            gTokens.comma,
            gTokens.int_value,
            gTokens.comma,
        ]

        self.run_test_failure(tokens, 
                              self.plocal
        )
    
    ##################################################################
    #
    def test_list_with_incorrect_item_type(self) :
        """test that a list with a wrong type item is rejected"""

        tokens = [
            gTokens.int_value,
            gTokens.comma,
            gTokens.string_value,
            gTokens.comma,
            gTokens.int_value
        ]

        self.run_test_failure(tokens, 
                              self.plocal
        )
    

##################################################################
##################################################################
#
class RepeatedParserTester(SequenceTypeParserTester) :
    """test the parse_repeated method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        SequenceTypeParserTester.__init__(self, n)

    ##################################################################
    #
    def make_int_seq_2_parser(self, min_count, max_count) :
        def parser(p) :
            def sub() :
                return p.parse_sequence(
                    p.parse_integer_value,
                    p.parse_integer_value
                )
            return p.parse_repeated(sub, min_count, max_count)

        return parser

    ##################################################################
    #
    def test_repeated_sequence_1_time(self) :
        """parse a repeated sequence with valid input"""

        values = gTokens.as_values(gTokens_I_2)

        def subv(a) :
            v = [self.make_int_verifier(values[0]), 
                 self.make_int_verifier(values[1])]
            self.assertAstSequence(a, v)

        def topv(a) :
            v = [subv]
            self.assertAstSequence(a, v)

        self.run_test_success(
            gTokens_I_2, 
            self.make_int_seq_2_parser(0, 1), 
            gTokens.as_text(gTokens_I_2), 
            topv
        )

    ##################################################################
    #
    def test_repeated_sequence_0_times(self) :
        """parse a repeated sequence with insufficient input and zero count allowed"""

        self.run_test_success(gTokens_I, 
                              self.make_int_seq_2_parser(0, 1),
                              gTokens.as_text([]),
                              self.assertAstNull
        )

    ##################################################################
    #
    def test_repeated_sequence_failure(self) :
        """parse a repeated sequence with insufficient input and zero count disallowed"""

        self.execute_test_case_failure(
            [gTokens_I], 
            self.make_int_seq_2_parser(1, 1000)
        )

    ##################################################################
    #
    def test_repeated_integer(self) :
        """parse a repeated sequence with various inputs"""

        def subparser(p) :
            return p.parse_repeated(p.parse_integer_value, 1, 3)

        for tokenstream in [gTokens_I, gTokens_I_2, gTokens_I_3] :
            self.execute_test_case_success(
                [tokenstream], 
                tokenstream,
                subparser
            )

        self.execute_test_case_success(
            [gTokens_I_4], 
            gTokens_I_3,
            subparser
        )


##################################################################
#
#
class OneOfParserTester(SequenceTypeParserTester) :
    """test the parse_one_of method"""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        SequenceTypeParserTester.__init__(self, n)

    ##################################################################
    #
    def subparser(self, p) :
        return p.parse_one_of(p.parse_integer_value,
                              p.parse_float_value)

    ##################################################################
    #
    def test_no_input(self) :
        """parse alternatives with failure on no input"""

        self.run_test_failure([], self.subparser)

    ##################################################################
    #
    def test_with_input(self) :
        """parse alternatives with success"""

        self.run_test_success(
            gTokens_I,
            self.subparser,
            gTokens.as_text(gTokens_I),
            lambda a : self.assertAstInteger(
                a, 
                gTokens.as_values(gTokens_I)[0]
            )
        )

        self.run_test_success(
            gTokens_F,
            self.subparser,
            gTokens.as_text(gTokens_F),
            lambda a : self.assertAstFloat(
                a, 
                gTokens.as_values(gTokens_F)[0]
            )
        )

    ##################################################################
    #
    def test_wrong_input(self) :
        """parse alternatives with failure and real input"""

        self.run_test_failure(gTokens_KW, self.subparser)

    ##################################################################
    #
    def test_complex_parser(self) :
        """parse alternatives with more complex input"""

        def localparser(p) :
            def p2() :
                return p.parse_sequence(
                    p.parse_integer_value,
                    p.parse_integer_value
                )
            return p.parse_one_of(p.parse_float_value, p2)

        self.execute_test_case_success([gTokens_I_2], gTokens_I_2, localparser)



##################################################################
#
#
class ExpressionParserTester(ParserTester) :    
    """test the ExpressionParser"""

    ##################################################################
    #
    def __init__(self, n='runTest', tokens=[]) :
        ParserTester.__init__(self, n, tokens)
        
    ##################################################################
    #
    def init_parser(self, contents=[]) :
        """Create an ExpressionParser with the contents"""
        buf    = testbuffer.TestBuffer(contents)
        parser = ExpressionParser(buf)
        return parser

    ##################################################################
    #
    def subparser(self, p) :
        """Always use parse_expression() to parse expressions"""

        return p.parse_expression()

    ##################################################################
    #
    def simple_test(self, tokens, verifier) :
        """Run a test to parse an atomic type as an expression"""

        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : verifier(a, gTokens.as_values(tokens)[0])
        )

    ##################################################################
    #
    def test_integer(self) :
        """parse a stream consisting on only a single integer"""

        # 1 ==> INTEGER
        self.simple_test(gTokens_I, self.assertAstInteger)

        value = gTokens.as_values(gTokens_I)[0]
        def verify(ast, value) :
            self.assertAstSigned(ast, value, self.assertAstInteger)

        # -1 ==> INTEGER
        tokens = gTokens_I[:]
        tokens.insert(0, gTokens.subtract)
        self.simple_test(tokens, verify)

        # +1 ==> INTEGER
        tokens = gTokens_I[:]
        tokens.insert(0, gTokens.add)
        self.simple_test(tokens, verify)

    ##################################################################
    #
    def test_float(self) :
        """parse a stream consisting on only a single float"""

        # 0.25 ==> FLOAT
        self.simple_test(gTokens_F, self.assertAstFloat)

        value = gTokens.as_values(gTokens_F)[0]
        def verify(ast, value) :
            self.assertAstSigned(ast, value, self.assertAstFloat)

        # -0.25 ==> FLOAT
        tokens = gTokens_F[:]
        tokens.insert(0, gTokens.subtract)
        self.simple_test(tokens, verify)

        # +0.25 ==> FLOAT
        tokens = gTokens_F[:]
        tokens.insert(0, gTokens.add)
        self.simple_test(tokens, verify)


    ##################################################################
    #
    def test_identifier(self) :
        """parse a stream consisting on only a single identifier"""

        # some_name ==> IDENTIFIER
        self.simple_test(gTokens_ID, self.assertAstIdentifier)

        value = gTokens.as_values(gTokens_ID)[0]
        def verify(ast, value) :
            self.assertAstSigned(ast, value, self.assertAstIdentifier)

        # -some_name ==> IDENTIFIER
        tokens = gTokens_ID[:]
        tokens.insert(0, gTokens.subtract)
        self.simple_test(tokens, verify)

        # +some_name ==> IDENTIFIER
        tokens = gTokens_ID[:]
        tokens.insert(0, gTokens.add)
        self.simple_test(tokens, verify)


    ##################################################################
    #
    def test_parenthesized(self) :
        """parse a stream consisting of a primary in parenthesis"""

        # ( 1 ) ==> INTEGER
        tokens = [gTokens.lparen, gTokens.int_value, gTokens.rparen]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.assertAstInteger(
                a, 
                gTokens.as_values([tokens[1]])[0]
            )
        )

        # - ( 1 ) ==> INTEGER
        tokens = [
            gTokens.subtract, 
            gTokens.lparen, 
            gTokens.int_value, 
            gTokens.rparen
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.assertAstSigned(
                a, 
                gTokens.as_values([tokens[1]])[0],
                self.assertAstInteger
            )
        )


    ##################################################################
    #
    def test_add_ops(self) :
        """parse a simple addition and subtraction"""

        # 1 + 0.5 => (* 1 0.5)
        tokens = [gTokens.int_value, gTokens.add, gTokens.float_value]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # some_name + some_other_name ==> (+ some_name, some_other_name)
        tokens = [gTokens.identifier, gTokens.add, gTokens.identifier]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # 1 + 0.5 + 0.5 ==> (+ (+ 1 0.5) 0.5)
        tokens = [
            gTokens.int_value, 
            gTokens.add, 
            gTokens.float_value,
            gTokens.add, 
            gTokens.float_value,
            
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # 1 + 0.5 - 0.5 ==> (- (+ 1 0.5) 0.5)
        tokens = [
            gTokens.int_value, 
            gTokens.add, 
            gTokens.float_value,
            gTokens.subtract, 
            gTokens.float_value,
            
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # 1 + 0.5 - ==> FAILURE
        tokens = [
            gTokens.int_value, 
            gTokens.add, 
            gTokens.float_value,
            gTokens.subtract, 
            
        ]
        self.run_test_failure(
            tokens,
            self.subparser
        )

    ##################################################################
    #
    def test_mul_ops(self) :
        """parse a simple multiplication and division"""

        # 1 * 0.5 ==> (* 1 0.5)
        tokens = [gTokens.int_value, gTokens.multiply, gTokens.float_value]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # some_name / 1 * 0.5 ==> (* (/ some_name 1) 0.5)
        tokens = [
            gTokens.identifier,
            gTokens.divide,
            gTokens.int_value, 
            gTokens.multiply, 
            gTokens.float_value
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # some_name / 1 * ==> FAILURE
        tokens = [
            gTokens.identifier,
            gTokens.divide,
            gTokens.int_value, 
            gTokens.multiply
        ]
        self.run_test_failure(
            tokens,
            self.subparser
        )

    ##################################################################
    #
    def test_exp_ops(self) :
        """parse a simple exponentiation"""

        # 1 ** 0.5 ==> (** 1 0.5)
        tokens = [gTokens.int_value, gTokens.exponent, gTokens.float_value]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # 1 ** some_name ** 0.5 ==> (** 1 (** some_name 0.5))
        tokens = [
            gTokens.int_value, 
            gTokens.exponent, 
            gTokens.identifier,
            gTokens.exponent, 
            gTokens.float_value
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

    ##################################################################
    #
    def test_funcall(self) :
        """parse a simple function call"""

        def local_assert(a) :
            """Just make sure we got a function call out of the parse"""
            self.assertAstFuncall(
                a, 
                gTokens.as_text([gTokens.identifier]),
                []
            )

        # fn() ==> FUNCALL
        tokens = [gTokens.identifier, gTokens.lparen, gTokens.rparen]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            local_assert
        )

        # fn(1) ==> FUNCALL
        tokens = [
            gTokens.identifier, 
            gTokens.lparen, 
            gTokens.int_value,
            gTokens.rparen
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            local_assert
        )

        # fn(1,1*0.2)  ==> FUNCALL
        tokens = [
            gTokens.identifier, 
            gTokens.lparen, 
            gTokens.int_value,
            gTokens.comma,
            gTokens.int_value,
            gTokens.multiply,
            gTokens.float_value,
            gTokens.rparen
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            local_assert
        )

        # fn('string')  ==> FUNCALL
        # strings can be function args too!
        tokens = [
            gTokens.identifier, 
            gTokens.lparen, 
            gTokens.string_value,
            gTokens.rparen
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            local_assert
        )
        
    ##################################################################
    #
    def test_mixed_ops(self) :
        """parse an expression with mixed precedence operations"""

        # 1 * 0.5 + some_name ==> (+ (* 1 0.5) some_name)
        tokens = [
            gTokens.int_value, 
            gTokens.multiply, 
            gTokens.float_value,
            gTokens.add,
            gTokens.identifier
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # 1 + 0.5 * some_name ==> (+ 1 (* 0.5 some_name))
        tokens = [
            gTokens.int_value, 
            gTokens.add,
            gTokens.float_value,
            gTokens.multiply, 
            gTokens.identifier
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

        # ((1 + 0.5)) * some_name ==> (* (+ 1 0.5) some_name)
        tokens = [
            gTokens.lparen,
            gTokens.lparen,
            gTokens.int_value, 
            gTokens.add,
            gTokens.float_value,
            gTokens.rparen,
            gTokens.rparen,
            gTokens.multiply, 
            gTokens.identifier
        ]
        self.run_test_success(
            tokens,
            self.subparser,
            gTokens.as_text(tokens),
            lambda a : self.just_pass(a)
        )

