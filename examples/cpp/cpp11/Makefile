

CPP=/sapmnt/appl_sw/gcc-4.7/bin/g++
CPPFLAGS=-g -std=c++11

all : pointertest treetest

pointertest : counted.h counted.cpp pointertest.cpp
	$(CPP) $(CPPFLAGS) -c counted.cpp
	$(CPP) $(CPPFLAGS) -c pointertest.cpp
	$(CPP) $(CPPFLAGS) -o pointertest pointertest.o counted.o

treetest : treenode.h sequence.h treetest.cpp
	$(CPP) $(CPPFLAGS) -c treetest.cpp
	$(CPP) $(CPPFLAGS) -o treetest treetest.o




