OBJS       =	\
		ExpSolver.o \
		ExponentialGenerator.o \
		ListMaker.o \
		UniformGenerator.o \
		util.o

BASEDIR    = $(shell pwd)/..
LIB        = libmklist.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+


