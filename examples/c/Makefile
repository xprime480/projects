
EXE = fvd redex

$(EXE) : % : %.c
	gcc -o $@ $<

test : $(EXE)
	./fvd
	./redex

