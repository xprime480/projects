
from datagentoken import *
import exprparser
from parsertools import Success, Failure

#######################################################
#######################################################
#
class DatagenConfigParser(exprparser.ExpressionParser) :
    """Class to parse Datagen configuration files"""

    #######################################################
    #
    def __init__(self, lexer) :
        """Initialize the instance."""

        exprparser.ExpressionParser.__init__(self, lexer)

    #######################################################
    #
    def parse_toplevel(self) :

        result = self.parse_one_of(
            self.parse_category_clause,
            self.parse_loop_clause,
            self.parse_name_decl_clause,
            self.parse_io_clause,
            self.parse_eof
        )

        if isinstance(result, Failure) :
            return Failure(
                'DatagenConfigParser.parse_toplevel failed to match',
                cascade = result
            )
        
        return result

        
    #######################################################
    #
    def parse_category_clause(self) :
            
        result = self.parse_sequence(
            self.parse_list_keyword, 
            self.parse_colon, 
            self.parse_name_list)

        if not result :
            return Failure('parse_category_clause: No result from parser')
            
        if isinstance(result, Failure) :
            return Failure(
                'parse_category_clause failed to match', 
                cascade = result
            )
        
        # repackage this later

        ast = result.ast
        if not ast or len(ast) < 5 :
            return Failure(
                'parse_category_clause, badly formatted result from subparser',
                cascade = result
            )

        xnames = ast[4][2:len(ast[4]):2] # name list without punctuation
        names  = [x[1] for x in xnames]
        key    = ast[2][1]
        newast = ('CATEGORY', key, names)

        return Success(result.text, newast)

    #######################################################
    #
    def parse_loop_clause(self) :
            
        result = self.parse_sequence(
            self.parse_loop_keyword, 
            self.parse_colon, 
            self.parse_loop_args)

        if not result :
            return Failure('parse_loop_clause: No result from parser')
            
        if isinstance(result, Failure) :
            return Failure(
                'parse_loop_clause failed to match', 
                cascade = result
            )
        
        # repackage this later

        ast = result.ast
        if not ast or len(ast) < 5 or len(ast[4]) < 5:
            return Failure(
                'parse_loop_clause, badly formatted result from subparser',
                cascade = result
            )

        xprs   = ast[4][2:5]
        newast = ('LOOP', xprs[0], xprs[1], xprs[2])

        return Success(result.text, newast)

    #######################################################
    #
    def parse_name_decl_clause(self) :

        result = self.parse_sequence(
            self.parse_name, 
            self.parse_colon, 
            self.parse_decl)

        if not result :
            return Failure(
                'parse_name_decl_clause failed to match', 
                cascade = result
            )
            
        if isinstance(result, Failure) :
            return result

        ast = result.ast
        if not ast or len(ast) < 5 :
            return Failure(
                'parse_category_clause, badly formatted result from subparser',
                cascade = result
            )

        name = ast[2][1]
        decls = ast[4]

        if not decls or len(decls) < 6 : 
            return Failure(
                'parse_category_clause, badly formatted result from subparser',
                cascade = result
            )

        decl_type = decls[2][1]
        if decls[3][0] == 'NULL' :
            decl_fmt = None
        else :
            decl_fmt = decls[3][2][3][1]
        if decls[4][0] == 'NULL' :
            decl_form = None
        else :
            decl_form = decls[4][2][3]
        if decls[5][0] == 'NULL' :
            decl_range = None
        else :
            decl_range = decls[5]

        newast = ('DECL', name, decl_type, decl_fmt, decl_form, decl_range)

        return Success(result.text, newast)

    #######################################################
    #
    def parse_decl(self) :

        result = self.parse_sequence(
            self.parse_type_keyword, 
            self.parse_format_opt, 
            self.parse_as_opt,
            self.parse_range_opt)

        if not result :
            return Failure(
                'parse_decl failed to match', 
                cascade = result
            )
            
        if isinstance(result, Failure) :
            return result

        return result

    #######################################################
    #
    def parse_format_opt(self) :

        def clause() :
            return self.parse_sequence(
                self.parse_format_keyword, 
                self.parse_string_value
            )

        return self.parse_repeated(clause, 0, 1)

    #######################################################
    #
    def parse_as_opt(self) :

        def clause() :
            return self.parse_sequence(
                self.parse_as_keyword, 
                self.parse_expression
            )

        return self.parse_repeated(clause, 0, 1)

    #######################################################
    #
    def parse_range_opt(self) :

        def clause() :
            return self.parse_sequence(
                self.parse_range_keyword, 
                self.parse_range_args
            )

        rv = self.parse_repeated(clause, 0, 1)
        if rv.ast[0] == 'NULL' :
            return rv

        return Success(rv.text, rv.ast[2][3])

    #######################################################
    #
    def parse_io_clause(self) :

        result = self.parse_sequence(
            self.parse_io_keyword, 
            self.parse_colon, 
            self.parse_string_value)

        if not result :
            return Failure(
                'parse_io_clause failed to match', 
                cascade = result
            )
            
        if isinstance(result, Failure) :
            return result
        
        # repackage this later

        ast = result.ast
        if not ast or len(ast) < 5 :
            return Failure(
                'parse_category_clause, badly formatted result from subparser',
                cascade = result
            )

        io_type = ast[2][1]
        io_file = ast[4][1]
        newast = ('IO', io_type, io_file)

        return Success(result.text, newast)

    #######################################################
    #

    def parse_list_keyword(self) :
        return self.parse_by_category([ListKwd])

    def parse_loop_keyword(self) :
        return self.parse_by_category([Loop])

    def parse_io_keyword(self) :
        return self.parse_by_category([IOKwd])

    def parse_type_keyword(self) :
        return self.parse_by_category([Type])

    def parse_format_keyword(self) :
        return self.parse_by_category([Format])

    def parse_as_keyword(self) :
        return self.parse_by_category([As])

    def parse_range_keyword(self) :
        return self.parse_by_category([Range])

    def parse_range_args(self) :
        return self.parse_repeated(self.parse_primitive, 2, 3)

    def parse_loop_args(self) :
        return self.parse_repeated(self.parse_expression, 3, 3)

    def parse_colon(self) :
        return self.parse_by_category([Colon])

    def parse_comma(self) :
        return self.parse_by_category([Comma])

    def parse_name_list(self) :
        return self.parse_list(self.parse_name, self.parse_comma)

    def parse_name(self) :
        return self.parse_identifier()
