

FILES ?=	BeautifulSoup.py	\
		combinator.py		\
		csvfileio.py		\
		logit.py		\
		parameters.py		\
		rangetools.py

TESTS ?=	rangetoolstest.py	\
		combinatortest.py	\
		logittest.py		\
		csvfileiotest.py	\
		parameterstest.py

DESTDIR ?= $(HOME)/lib/python

install :
	@for f in $(FILES) ; \
		do diff -q $$f $(DESTDIR)/$$f >/dev/null || \
		( echo "Installing $$f" && cp -p $$f $(DESTDIR)/$$f ); \
	done

test :
	@for f in $(TESTS) ; \
		do echo $$f; python3 -m unittest $$f; \
	done
