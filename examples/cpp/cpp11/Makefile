

CPP=/sapmnt/appl_sw/gcc-4.7/bin/g++
CPPFLAGS=-g -std=c++11
TESTS=pointertest treetest lambdatest
LIB=libcpp11.a
LIBSRC=$(shell ls *.cpp | grep -v ^main_)
LIBOBJ=$(LIBSRC:.cpp=.o)
HDRS=(shell *.h)

all : $(TESTS)

pointertest : $(LIB) main_pointertest.cpp
	$(CPP) $(CPPFLAGS) -o pointertest main_pointertest.cpp -L. -lcpp11

treetest : $(LIB) main_treetest.cpp
	$(CPP) $(CPPFLAGS) -o treetest main_treetest.cpp -L. -lcpp11

lambdatest : $(LIB) main_lambdatest.cpp
	$(CPP) $(CPPFLAGS) -o lambdatest main_lambdatest.cpp -L. -lcpp11

$(LIB) : $(LIBSRC) $(HDRS)
	$(CPP) $(CPPFLAGS) -c counted.cpp
	$(CPP) $(CPPFLAGS) -c pointertest.cpp
	$(CPP) $(CPPFLAGS) -c treetest.cpp
	$(CPP) $(CPPFLAGS) -c lambdatest.cpp
	@-rm $(LIB)
	ar cr $(LIB) $(LIBOBJ)



