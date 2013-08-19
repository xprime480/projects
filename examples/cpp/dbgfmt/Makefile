
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

MYEXE = Buffer debugdump4

all : $(MYEXE)

include ../mk_deps.mk

$(OBJS) : %.o : %.cpp
	g++ $(CFLAGS) -c  -g -o $@ $<

$(MYEXE) : % : $(DEPS) %.o
	g++ -o $@ $<
