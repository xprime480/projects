# GENERIC makefile

all : $(MYEXE)

OBJS      = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CPP       = g++
CPP_FLAGS = -std=c++11 -Wall -Werror -g

include $(BASEDIR)/mk_deps.mk

$(OBJS) : %.o : %.cpp
	$(CPP) $(CPP_FLAGS) -c  -g -o $@ $<

$(MYEXE): $(DEPS) $(OBJS)
	$(CPP) -o $(MYEXE) $(OBJS)

test : $(MYEXE)
	./$(MYEXE) $(TEST_ARGS)

clean :
	-rm *.o *.exe *~ *.d $(CLEAN_FILES)

