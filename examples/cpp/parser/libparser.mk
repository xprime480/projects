OBJS       = 	Expression.o			\
		Parser.o			\
		SingleCharParser.o		\
		AnyCharOfParser.o		\
		AnyOfParser.o			\
		SequenceOfParser.o		\
		ZeroOneOfParser.o		\
		OnePlusOfParser.o		\
		SymbolStreamParser.o		\
		CharacterStream.o		\
		FileCharacterStream.o		\
		StringCharacterStream.o		\
		Token.o				\
		TokenStream.o			\
		CharTokenStream.o		\
		BasicTokenStream.o

BASEDIR    = $(shell pwd)/..
LIB        = libparser.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+


