OBJS       = 	SkelHelper.o

BASEDIR    = $(shell pwd)/..
LIB        = libskel.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+


