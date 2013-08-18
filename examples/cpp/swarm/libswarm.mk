OBJS       = PPA.o Particle.o Products.o Rules.o Swarm.o Utils.o
BASEDIR    = $(shell pwd)/..
LIB        = libswarm.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+


