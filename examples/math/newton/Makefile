EXE_LIST   = newton_test
LOCAL_TEST = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	./newton_test
	./newton_test 7
	./newton_test 8 3
	./newton_test 100 35


