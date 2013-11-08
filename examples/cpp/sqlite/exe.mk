
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lrapper

include $(BASEDIR)/generic.mk

lib :
	make -f librapper.mk lib
