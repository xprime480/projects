
OBJS         = $(MYEXE).o
BASEDIR      = $(shell pwd)/..
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lapr

include $(BASEDIR)/generic.mk

lib :
	make -f libapr.mk lib
