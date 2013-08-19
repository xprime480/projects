
EXE_LIST   = approxmatch trietest
LOCAL_TEST = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	time ./trietest ~/tmp/randomwords.txt en_
	time ./trietest ~/tmp/randomwords.txt 10freedesktop
	./approxmatch kittle bittle
	./approxmatch was saw
	./approxmatch sdfkasdfdkfsdf ''
	./approxmatch abcdef abcdez
	./approxmatch abc xyz
	./approxmatch abcdefghijklmnopqurstu abcdefghijklmnopqurstu
	./approxmatch qwertyuiop asdfghjkl
