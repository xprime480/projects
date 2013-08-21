
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lperftest

include $(BASEDIR)/generic.mk

lib :
	make -f libperftest.mk lib
