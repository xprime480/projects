.PHONY : all clean

all : sqlparser

SRC = 	sqlparser.cpp			\
	Expression.cpp			\
	Parser.cpp			\
	SingleCharParser.cpp		\
	AnyCharOfParser.cpp		\
	AnyOfParser.cpp			\
	SequenceOfParser.cpp		\
	ZeroOneOfParser.cpp		\
	OnePlusOfParser.cpp		\
	SymbolParser.cpp		\
	SymbolStreamParser.cpp		\
	KeywordParser.cpp		\
	CharacterStream.cpp		\
	FileCharacterStream.cpp		\
	StringCharacterStream.cpp	\
	Token.cpp			\
	TokenStream.cpp			\
	CharTokenStream.cpp		\
	BasicTokenStream.cpp		\
	SqlParser.cpp			\
	SqlKeywords.cpp			\
	SqlCreateParser.cpp		\
	SqlCreateTableParser.cpp	\
	SqlTokenStream.cpp

OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

sqlparser : $(OBJ)
	g++ $(CFLAGS) -g -o $@ $+

$(OBJ) : %.o : %.cpp
	g++ $(CFLAGS) -g -c $<

%.d: %.cpp
	@echo Building dependencies for $< && \
	set -e; g++ -MM $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

clean : 
	@-rm $(OBJ) $(DEP) *~

-include $(DEP)
