
FILES ?= $(wildcard *.el)

DESTDIR ?= $(HOME)/elisp

.PHONY : install test

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || \
		( echo "Installing $$f" && rm -f $(DESTDIR)/$$f && cp -p $$f $(DESTDIR)/$$f ); \
	done

#test :
#	make -C test test
