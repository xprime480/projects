
EXE_LIST   = mklist edsolver
LOCAL_TEST = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	./edsolver 50 15
	./mklist -s
	./mklist -s -p 1 -e 20
	./mklist -s -p 1 -l 100 -e 33 -o 15
