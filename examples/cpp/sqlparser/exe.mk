
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lsqlparser

include $(BASEDIR)/generic.mk

lib :
	make -f libsqlparser.mk lib
