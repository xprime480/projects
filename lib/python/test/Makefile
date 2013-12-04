

TESTS ?= $(wildcard test*.py)
PERF  ?= $(wildcard perf*.py)
TESTFLAGS ?= -v -f

test :
	@for f in $(TESTS) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH python3 -m unittest $(TESTFLAGS) $$f; \
	done

perf :
	@for f in $(PERF) ; \
		do echo $$f; PYTHONPATH=..:$$PYTHONPATH ./$$f; \
	done
