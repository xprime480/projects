OBJS =	Expression.o			\
	Parser.o			\
	SingleCharParser.o		\
	AnyCharOfParser.o		\
	AnyOfParser.o			\
	SequenceOfParser.o		\
	ZeroOneOfParser.o		\
	OnePlusOfParser.o		\
	SymbolParser.o			\
	SymbolStreamParser.o		\
	KeywordParser.o			\
	CharacterStream.o		\
	FileCharacterStream.o		\
	StringCharacterStream.o		\
	Token.o				\
	TokenStream.o			\
	CharTokenStream.o		\
	BasicTokenStream.o		\
	SqlParser.o			\
	SqlKeywords.o			\
	SqlCreateParser.o		\
	SqlCreateTableParser.o		\
	SqlTokenStream.o

BASEDIR    = $(shell pwd)/..
LIB        = libsqlparser.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+


