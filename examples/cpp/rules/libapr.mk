OBJS       = Linear.o PosetItems_2D.o Dim5.o
BASEDIR    = $(shell pwd)/..
LIB        = libapr.a

include $(BASEDIR)/generic.mk

lib : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+
