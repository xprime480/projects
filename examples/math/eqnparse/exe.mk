
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/../../cpp
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -leqnparse

include $(BASEDIR)/generic.mk

lib :
	make -f libeqnparse.mk lib
