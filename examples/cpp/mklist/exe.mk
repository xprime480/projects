
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lmklist

include $(BASEDIR)/generic.mk

lib :
	make -f libmklist.mk lib
