CPP = g++
CC  = gcc

LIBS = SqliteDB.o SqliteDbHeader.o


all : rapper

rapper : rapper.o $(LIBS)
	$(CPP) -o $@ $^

rapper.o $(LIBS) : %.o : %.cpp
	$(CPP) -g -c $<

test : rapper
	./rapper test.seb


