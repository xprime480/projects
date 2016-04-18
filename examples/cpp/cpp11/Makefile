

CPP=/sapmnt/appl_sw/gcc-4.7/bin/g++
CPPFLAGS=-g -std=c++11
TESTS=pointertest treetest

all : $(TESTS)

pointertest : lib main_pointertest.cpp
	$(CPP) $(CPPFLAGS) -o pointertest main_pointertest.cpp pointertest.o counted.o

treetest : lib main_treetest.cpp
	$(CPP) $(CPPFLAGS) -o treetest main_treetest.cpp treetest.o

lib : treenode.h sequence.h treetest.cpp counted.h counted.cpp pointertest.cpp
	$(CPP) $(CPPFLAGS) -c counted.cpp
	$(CPP) $(CPPFLAGS) -c pointertest.cpp
	$(CPP) $(CPPFLAGS) -c treetest.cpp



