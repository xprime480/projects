.PHONY : all clean

all : lazyseq

SRC = 	lazyseq.cpp \
	Fibonacci.cpp \
	Hamming.cpp \
	GeneralizedHamming.cpp \
	LazyExpression.cpp \
	LazyForm.cpp \
	LazyInterp.cpp \
	LazySeq.cpp \
	TokenStream.cpp

OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

CFLAGS += -Wall

lazyseq : $(OBJ)
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
