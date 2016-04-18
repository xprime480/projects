

CPP=/sapmnt/appl_sw/gcc-4.7/bin/g++
CPPFLAGS=-g -std=c++11
TESTS=pointertest treetest lambdatest
LIB=libcpp11.a
LIBSRC=$(shell ls *.cpp | grep -v ^main_)
LIBOBJ=$(LIBSRC:.cpp=.o)
LIBDEP=$(LIBSRC:.cpp=.d)
HDRS=$(shell ls *.h)

all : $(TESTS)

$(TESTS) : % : main_%.cpp $(LIB) 
	$(CPP) $(CPPFLAGS) -o $* $< -L. -lcpp11

$(LIB) : $(LIBOBJ)
	@-rm $(LIB)
	ar cr $(LIB) $(LIBOBJ)

$(LIBOBJ) : %.o : %.cpp
	$(CPP) $(CPPFLAGS) -c $<

$(LIBDEP) : %.d : %.cpp $(HDRS)
	$(CPP) $(CPPFLAGS) -MM $< -o $*.d

clean : 
	@-rm *~ *.o *.d $(LIB)

include $(LIBDEP)
