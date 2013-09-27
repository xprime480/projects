
EXE_LIST   = rapper
LOCAL_TEST = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	./rapper random_test.sqlite
