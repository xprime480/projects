# GENERIC makefile

all : $(MYEXE)

BASEDIR    ?= .
OBJS       ?= $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CPP         = g++
CPP_FLAGS   = -std=c++11 -Wall -Werror -g
LINK_FLAGS  = -L$(BASEDIR)/lib

include $(BASEDIR)/mk_deps.mk

$(OBJS) : %.o : %.cpp
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

$(MYEXE): $(EXTRA_TARGET) $(DEPS) $(OBJS)
	$(CPP) $(CPP_FLAGS) $(LINK_FLAGS) -o $(MYEXE) $(OBJS) $(EXTRA_LIBS)

test : $(MYEXE) $(LOCAL_TEST)
	./$(MYEXE) $(TEST_ARGS)

clean :
	-rm *.o *.exe *~ *.d $(CLEAN_FILES)

