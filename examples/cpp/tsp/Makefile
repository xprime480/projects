

BASEDIR      = $(shell pwd)/..
MYEXE        = tsp
TEST_ARGS   ?= problem2
CLEAN_FILES  = *.out

include $(BASEDIR)/generic.mk

ltest : test
	tail -1 $(TEST_ARGS).out
