OBJS       = 	Equation.o Parser.o Token.o


BASEDIR    = $(shell pwd)/../../cpp
LIB        = libeqnparse.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+



