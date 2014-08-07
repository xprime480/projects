
OBJS         = $(MYEXE).o
BASEDIR      = $(HOME)/working/examples/cpp
EXTRA_TARGET = lib
EXTRA_LIBS   = -L. -lac++

include $(BASEDIR)/generic.mk

lib :
	make -f libac++.mk lib
