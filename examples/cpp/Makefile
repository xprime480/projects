
EXE = wchar boing tov tol ptrscan

$(EXE) : % : %.cpp
	g++ -std=c++0x -g -o $@ $<

test : $(EXE)
	@-for exe in $(EXE) ; do echo '*** Testing: ' $${exe} ; ./$${exe} ; done
