
LIB = ../lib/libutils.a
EXTRA_INCLUDES = -I../include

all : $(LIB)

SRC = 	mathutils.cpp strdup.cpp

OBJ = $(SRC:.cpp=.o)

CFLAGS = -std=c++11 -Wall -Werror -g

$(LIB) : $(OBJ)
	-rm $@
	ar cr $@ $+

$(OBJ) : %.o : %.cpp
	g++ $(CFLAGS) $(EXTRA_INCLUDES) -c $<

include ../dep.mk

