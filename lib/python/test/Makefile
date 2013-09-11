

TESTS ?=	rangetoolstest.py	\
		combinatortest.py	\
		logittest.py		\
		csvfileiotest.py	\
		parameterstest.py

test :
	@for f in $(TESTS) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH python3 -m unittest $$f; \
	done
