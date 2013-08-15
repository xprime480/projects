
SRC = tspmain.cpp TSP.cpp Point2D.cpp
OBJ = $(SRC:.cpp=.o)
EXE = tsp

CFLAGS = -std=c++11 -Wall -Werror -g

all : $(EXE)

$(EXE) : $(OBJ)
	g++ $(CFLAGS) -o $@ $+

$(OBJ) : %.o : %.cpp
	g++ $(CFLAGS) -c $<

clean :
	-rm *.o *.exe *~

TEST = problem4

test : $(EXE)
	./tsp $(TEST)
	tail -1 $(TEST).out
