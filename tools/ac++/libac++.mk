OBJS       = 	Analyzer.o	\
		ArgParser.o

BASEDIR    = $(HOME)/working/examples/cpp
LIB        = libac++.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+
