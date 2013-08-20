OBJS       = 	Fibonacci.o \
		Hamming.o \
		GeneralizedHamming.o \
		LazyExpression.o \
		LazyForm.o \
		LazyInterp.o \
		LazySeq.o \
		TokenStream.o

BASEDIR    = $(shell pwd)/..
LIB        = liblazyseq.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+
