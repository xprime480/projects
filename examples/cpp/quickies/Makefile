
EXE_LIST   ?= $(patsubst %.cpp,%,$(wildcard *.cpp))
LOCAL_TEST  = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	for x in $(EXE_LIST) ; do  ./$${x} ; done


