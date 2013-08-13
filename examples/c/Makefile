
EXE = fvd redex var

$(EXE) : % : %.c
	gcc -o $@ $<

test : $(EXE)
	@-for exe in $(EXE) ; do echo $${exe} ; ./$${exe} ; done

