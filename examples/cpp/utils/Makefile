
LIB = ../lib/libutils.a
EXTRA_INCLUDES = -I../include


all : $(LIB)

SRC = 	mathutils.cpp strdup.cpp

OBJ = $(SRC:.cpp=.o)

CPP    = /sapmnt/appl_sw/gcc-4.7/bin/g++
CFLAGS = -std=c++11 -Wall -Werror -g

$(LIB) : $(OBJ)
	-rm $@
	ar cr $@ $+

$(OBJ) : %.o : %.cpp
	$(CPP) $(CFLAGS) $(EXTRA_INCLUDES) -c $<

include ../dep.mk

