
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lapproxmatch

include $(BASEDIR)/generic.mk

lib :
	make -f libapproxmatch.mk lib
