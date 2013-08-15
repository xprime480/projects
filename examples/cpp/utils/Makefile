
LIB = ../lib/libutils.a
EXTRA_INCLUDES = -I../include

all : $(LIB)

SRC = 	mathutils.cpp

OBJ = $(SRC:.cpp=.o)

$(LIB) : $(OBJ)
	-rm $@
	ar cr $@ $+

$(OBJ) : %.o : %.cpp
	g++ $(CFLAGS) $(EXTRA_INCLUDES) -g -c $<

include ../dep.mk

