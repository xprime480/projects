OBJS =	PerfTest.o		\
	PerfTest_AOFLS.o	\
	PerfTest_AOFS.o		\
	PerfTest_PA.o		\
	PerfTest_PV.o		\
	PerfTest_VOFLS.o	\
	PerfTest_VOFS.o


BASEDIR    = $(shell pwd)/..
LIB        = libperftest.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+
