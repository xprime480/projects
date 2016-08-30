# GENERIC makefile

all : $(MYEXE)

BASEDIR    ?= .
OBJS       ?= $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CPP         = /sapmnt/appl_sw/gcc-4.7/bin/g++
CPP_FLAGS   = -std=c++11 -Wall -Werror -g -I$(BASEDIR)/include
LINK_FLAGS  = -L$(BASEDIR)/lib -lutils -lstdc++

include $(BASEDIR)/mk_deps.mk

$(OBJS) : %.o : %.cpp
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

$(MYEXE): $(EXTRA_TARGET) $(DEPS) $(OBJS)
	$(CPP) $(CPP_FLAGS) -o $(MYEXE) $(OBJS) $(EXTRA_LIBS) $(LINK_FLAGS)

test : $(MYEXE) $(LOCAL_TEST)
	./$(MYEXE) $(TEST_ARGS)

clean :
	-rm *.o *.exe *~ *.d $(CLEAN_FILES) *.a

