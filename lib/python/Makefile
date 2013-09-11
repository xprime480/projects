

FILES ?=	BeautifulSoup.py	\
		combinator.py		\
		csvfileio.py		\
		logit.py		\
		parameters.py		\
		rangetools.py

DESTDIR ?= $(HOME)/lib/python

.PHONY : install test

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || \
		( echo "Installing $$f" && cp -p $$f $(DESTDIR)/$$f ); \
	done

test :
	make -C test test
