
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lskel

include $(BASEDIR)/generic.mk

lib :
	make -f libskel.mk lib
