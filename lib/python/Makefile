

FILES =	BeautifulSoup.py	\
	combinator.py		\
	datagenfile.py		\
	logit.py		\
	rangetools.py

DESTDIR ?= $(HOME)/lib/python

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || cp -p $$f $(DESTDIR)/$$f; \
	done
