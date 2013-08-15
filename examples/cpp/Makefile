
EXE = 	wchar boing tov tol ptrscan sim2 qsim trie anonseq anonseqlazy \
	anonseqlazy2 tr1test
EXE = 	tr1test


$(EXE) : % : %.cpp
	g++ -std=c++11 -g -o $@ $<

test : $(EXE)
	@-for exe in $(EXE) ; do echo '*** Testing: ' $${exe} ; ./$${exe} ; done

clean :
	@-rm *.exe


