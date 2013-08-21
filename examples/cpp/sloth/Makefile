
EXE_LIST   = sloth
LOCAL_TEST = local_test

% :
	for x in $(EXE_LIST) ; do MYEXE=$${x} make -f exe.mk $@ ; done

local_test : all
	./skel Hello, World

DOCS = sloth.pdf

doc : $(DOCS)

$(DOCS) : %.pdf : %.tex
	latex $<
	latex $<
	dvips -o $*.ps $*.dvi
	ps2pdf $*.ps $@
	rm $*.dvi $*.ps

