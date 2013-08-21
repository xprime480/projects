OBJS       =	Appender.o \
		BinopGenerator.o \
		CountGenerator.o \
		DropGenerator.o \
		FibonacciGenerator.o \
		FixedSequenceGenerator.o \
		FlattenGenerator.o \
		Form.o \
		FormFactory.o \
		GeneralizedFibonacciGenerator.o \
		Infinite.o \
		Interp.o \
		ListGenerator.o \
		MinMaxGenerator.o \
		SequenceGenerator.o \
		SingletonGenerator.o \
		SliceGenerator.o \
		TakeGenerator.o \
		TakeIfGenerator.o \
		Tokenizer.o \
		UnopGenerator.o

BASEDIR    = $(shell pwd)/..
LIB        = libsloth.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+



SRC = 	
