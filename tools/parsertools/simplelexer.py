
import re
import simpletoken

#######################################################
#######################################################
#
class LexerError(BaseException) :
    """Class to encapsulate errors created by DatagenParser"""

    #######################################################
    #
    def __init__(self, err, lineno) :
        """Initialize the instance."""
        self.err    = err
        self.lineno = lineno

    #######################################################
    #
    def __str__(self) :
        """Return a string representation of the instance."""
        return '%s at line number %d ' % (repr(self.err), self.lineno)

#######################################################
#######################################################
#
class SimpleLexer(object) :
    #######################################################
    #
    def __init__(self) :
        # map a regular expression to a token type
        #
        self.res = [ (re.compile('(\A)([0-9]+\.[0-9]*)(.*)'), 
                      simpletoken.FloatValue()), 
                     (re.compile('(\A)([0-9]+)(.*)'),         
                      simpletoken.IntegerValue()), 
                     (re.compile('(\A)([a-zA-Z_][a-zA-Z_0-9]*)(.*)'), 
                      simpletoken.Identifier()) ]

        # map a string to a token type.  Overrides self.res.  Key when
        # checked is the text scanned to generate a token
        #
        self.token_types = {
            None : simpletoken.SimpleTokenType()
        }

        self.text = ''
        self.lineno = 1



    #######################################################
    #
    def add_token_type_regexp(self, regexp, ttype) :
        """Add a regular express to token type mapping

Client should call this for any multicharacter token that is not one of the
types described in the defaults for self.res

Priority is given to the last entry        
        """  

        ext_regexp = '(\A)(' + regexp + ')(.*)'
        entry      = (re.compile(ext_regexp), ttype)
        self.res.insert(0, entry)

    #######################################################
    #
    def add_token_type_simple(self, text, ttype) :
        """Add a mapping for text to a token type.

Overrides the default mappings for character strings to token types.  Defaults
are:
        * the values self.res for tokens which match one of the regexps;
        * 'Operator' for single char tokens;
        * 'SimpleTokenType' for multi-char tokens.

"""
        self.token_types[text.lower()] = ttype

    #######################################################
    #
    def add_text(self, text) :
        self.text += text

    #######################################################
    #
    def get_lineno(self) :
        return self.lineno

    #######################################################
    #
    def get_token(self) :
        #
        # skip whitespace and comments
        # at newline increment line counter
        #
        if self.skip_whitespace() :
            return None

        t = self.initial_scan()
        if t :
            return t

        #
        # Match various reserved symbols and/or words
        #
        tt = None

        for (re,ttype) in self.res :
            mo = re.match(self.text) 
            if mo :
                tt = ttype
                break

        if mo :
            token_text = mo.group(2)
            self.text = self.text[len(token_text):]
        else :
            token_text = self.text[0]
            self.text = self.text[1:]
            tt = simpletoken.Operator()

        tt = self.token_types.get(token_text.lower(), tt)
        return simpletoken.SimpleToken(self.lineno, token_text, tt)
        
    #######################################################
    #
    def skip_whitespace(self) :
        while True :
            self.text = self.text.lstrip(' \t')
            if not self.text :
                return True
            elif self.text[0] == '\n' :
                self.text    = self.text[1:]
                self.lineno += 1
            elif self.text[0] == '#' :
                self.text = self.text[1:]
                while self.text :
                    if self.text[0] == '\n' :
                        break
                    else :
                        self.text = self.text[1:]
            else :
                break

        return False

    #######################################################
    #
    def initial_scan(self) :
        return None
