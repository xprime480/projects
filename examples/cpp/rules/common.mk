
OBJS         = Linear.o PosetItems_2D.o Dim5.o
BASEDIR      = $(shell pwd)/..
EXTRA_LIBS   = $(OBJS)

include $(BASEDIR)/generic.mk

all : $(OBJS)
