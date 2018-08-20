
import re
import datagentoken
from simplelexer import LexerError, SimpleLexer

#######################################################
#######################################################
#
class DatagenLexer(SimpleLexer) :
    def __init__(self) :
        SimpleLexer.__init__(self)

    def initial_scan(self) :
        return self.scan_string()

    def scan_string(self) :
        if not self.text :
            return None
        if self.text[0] not in '"\'' :
            return None

        lineno = self.lineno
        quote = self.text[0]
        value = quote[:]

        self.text = self.text[1:]

        while self.text :
            if self.text[0] == quote :
                self.text = self.text[1:]
                value += quote
                return datagentoken.DatagenToken(lineno, 
                                                 value, 
                                                 datagentoken.StringValue())

            if self.text[0] == '\n' :
                self.lineno += 1

            if self.text[0] == '\\' :
                self.text = self.text[1:]
                if not self.text :
                    raise LexerError('Unterminated escape', self.lineno)

            value += self.text[0]
            self.text = self.text[1:]

            
        raise LexerError('Unterminated string constant', lineno)
        
