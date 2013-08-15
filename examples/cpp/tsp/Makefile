

BASEDIR = $(shell pwd)/..
MYEXE     = tsp
TEST_ARGS = problem2

include $(BASEDIR)/generic.mk

ltest : test
	tail -1 $(TEST_ARGS).out

lclean : clean
	-rm *.out

