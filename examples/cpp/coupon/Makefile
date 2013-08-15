
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

MYEXE = coupon

all : $(MYEXE)

include ../mk_deps.mk

$(OBJS) : %.o : %.cpp
	g++ $(CFLAGS) -c  -g -o $@ $<

$(MYEXE): $(DEPS) $(OBJS)
	g++ -o $(MYEXE) $(OBJS)

test : $(MYEXE)
	./$(MYEXE)
