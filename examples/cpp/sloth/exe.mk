
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lsloth

include $(BASEDIR)/generic.mk

lib :
	make -f libsloth.mk lib
