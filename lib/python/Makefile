

FILES =	BeautifulSoup.py	\
	combinator.py		\
	csvfileio.py		\
	logit.py		\
	parameters.py		\
	rangetools.py

TESTERS =	rangetoolstest.py	\
		combinatortest.py	\
		logittest.py

DESTDIR ?= $(HOME)/lib/python

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || cp -p $$f $(DESTDIR)/$$f; \
	done

test :
	@for f in $(TESTERS) ; \
		do echo $$f; python3 -m unittest $$f; \
	done
