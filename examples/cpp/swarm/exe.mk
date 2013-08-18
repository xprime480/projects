
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lswarm

include $(BASEDIR)/generic.mk

lib :
	make -f libswarm.mk lib
