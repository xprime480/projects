
FILES ?= $(wildcard *.py)
SUBDIRS ?= datatable

DESTDIR ?= $(HOME)/lib/python

.PHONY : install test

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || \
		( echo "Installing $$f" && rm -f $(DESTDIR)/$$f && cp -p $$f $(DESTDIR)/$$f ); \
	done
	@for d in $(SUBDIRS) ; \
		do find $$d -name '*.py' | xargs tar czvf - | (cd $(DESTDIR) && tar xzf - ) \
	done

test :
	make -C test test

perf :
	make -C test perf
