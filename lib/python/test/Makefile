

TESTS ?=	\
	combinatortest.py	\
	countingtest.py		\
	csvfileiotest.py	\
	logittest.py		\
	parameterstest.py	\
	rangetoolstest.py	\
	verscmptest.py

test :
	@for f in $(TESTS) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH python3 -m unittest $$f; \
	done
