

TESTS ?= $(wildcard *.py)

test :
	@for f in $(TESTS) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH python3 -m unittest -v -f $$f; \
	done
