
EXE_LIST   ?= $(patsubst %.cpp,%,$(wildcard *.cpp))
LOCAL_TEST  = local_test

all :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

#% : %.cpp
#	MYEXE=$@ make -f exe.mk $@
#
local_test : all
	for x in $(EXE_LIST) ; do  ./$${x} ; done

clean :
	make -f exe.mk clean
