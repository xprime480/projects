OBJS       = 	SqliteDB.o SqliteDbHeader.o

BASEDIR    = $(shell pwd)/..
LIB        = librapper.a

include $(BASEDIR)/generic.mk

lib : $(LIB)

$(LIB) : $(OBJS)
	-rm $(LIB)
	ar cr $(LIB) $+


