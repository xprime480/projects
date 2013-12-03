

TESTS ?= $(wildcard test*.py)
PERF  ?= $(wildcard perf*.py)

test :
	@for f in $(TESTS) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH python3 -m unittest -v -f $$f; \
	done

perf :
	@for f in $(PERF) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH ./$$f; \
	done
