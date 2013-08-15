
SRC  = tspmain.cpp TSP.cpp Point2D.cpp
OBJS = $(SRC:.cpp=.o)
EXE  = tsp

CPP_FLAGS = -std=c++11 -Wall -Werror -g

all : $(EXE)

include ../mk_deps.mk

$(EXE) : $(OBJS)
	g++ $(CPP_FLAGS) -o $@ $+

$(OBJS) : %.o : %.cpp
	g++ $(CPP_FLAGS) -c $<

clean :
	-rm *.o *.exe *~ *.d

TEST = problem4

test : $(EXE)
	./tsp $(TEST)
	tail -1 $(TEST).out
