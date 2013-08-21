
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

MYEXE = Test

all : $(MYEXE)

include ../mk_deps.mk

$(OBJS) : %.o : %.cpp
	g++ $(CFLAGS) -c  -g -o $@ $<

$(MYEXE): $(DEPS) $(OBJS)
	g++ -o $(MYEXE) $(OBJS)
