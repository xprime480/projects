
DEP = $(OBJ:.o=.d)

%.d: %.cpp
	@echo Building dependencies for $< && \
	set -e; g++ $(EXTRA_INCLUDES) -MM $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@

-include $(DEP)
