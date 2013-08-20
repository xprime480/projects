
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lparser

include $(BASEDIR)/generic.mk

lib :
	make -f libparser.mk lib
