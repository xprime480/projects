
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -llazyseq

include $(BASEDIR)/generic.mk

lib :
	make -f liblazyseq.mk lib
